// vim: set sw=2 ts=2 expandtab softtabstop=2:
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <vector>

using namespace llvm;


namespace {
struct ReplaceGetGlobalIDPass : public ModulePass {
  static char ID;
  ReplaceGetGlobalIDPass() : ModulePass(ID) { }

  bool runOnModule(Module& M) override {
    bool changed = false;
    Function* get_global_idF = M.getFunction("get_global_id");

    if (get_global_idF == 0) {
      // The function isn't used anywhere
      return false;
    }

    // get_global_id(x) === get_local_size(x)*get_group_id(x) + get_local_id(x)
    Function* get_local_sizeF = GetWorkItemFunction(M, "get_local_size");
    Function* get_group_idF = GetWorkItemFunction(M, "get_group_id");
    Function* get_local_idF = GetWorkItemFunction(M, "get_local_id");

    std::vector<CallInst*> foundCalls;
    for (Module::iterator FI = M.begin(), FE =M.end(); FI != FE; ++FI)
      for (Function::iterator BB = FI->begin(), BBE=FI->end(); BB != BBE; ++BB)
        for (BasicBlock::iterator i = BB->begin(), e = BB->end(); i!=e; ++i) {
          if (CallInst* CI =  dyn_cast<CallInst>(i)) {
            if ( CI->getCalledFunction() == get_global_idF ) {
              errs() << "Found :" << get_global_idF->getName() << "\n";
              // We can't do the modification here because we will
              // invalidate the instruction iterator when removing the call to get_global_id()
              foundCalls.push_back(CI);
            }
          }
        }

    for(std::vector<CallInst*>::iterator CI = foundCalls.begin(), CIE = foundCalls.end(); CI != CIE; ++CI) {
      // Get dimension argument
      assert((*CI)->getNumArgOperands() == 1 && "get_global_id is called with the wrong number of arguments");
      Value* dimension = (*CI)->getArgOperand(0);

      // Inject our instructions
      // %rpl.ggi.0. = call i32 @get_group_id(i32 0)
      // %rpl.ggi.1. = call i32 @get_local_size(i32 0)
      // %rpl.ggi.2. = mul i32 %rpl.ggi.0., %rpl.ggi.1.
      // %rpl.ggi.3. = call i32 @get_local_id(i32 0)
      // %rpl.ggi.result. = add i32 %rpl.ggi.2., %rpl.ggi.3.
      IRBuilder<> Builder(*CI);
      CallInst* ggiCall = Builder.CreateCall(get_group_idF, dimension, "rpl.ggi.0.");
      CallInst* glsCall = Builder.CreateCall(get_local_sizeF, dimension, "rpl.ggi.1.");
      Value* mul = Builder.CreateMul(ggiCall, glsCall, "rpl.ggi.2.");
      CallInst* gliCall = Builder.CreateCall(get_local_idF, dimension, "rpl.ggi.3.");
      Value* result = Builder.CreateAdd(mul, gliCall,"rpl.ggi.result.");

      // Replace all uses with
      (*CI)->replaceAllUsesWith(result);
      (*CI)->eraseFromParent(); // Finally we can remove the CallInst to get_global_id()
    }

    get_global_idF->eraseFromParent();
    return changed;
  }

  Function* GetWorkItemFunction(Module& M, StringRef functionName) {
    // Easy-path: The function is already in the module
    Constant* function = M.getFunction(functionName);
    if ( function && isa<Function>(function))
      return cast<Function>(function);

    // Harder-path: The function isn't already in the
    // module so we need to insert it

    // Are these types right for 64-bit?
    errs() << "Warning: " << functionName << "() was not in the module, guessing types and inserting\n";
    function = M.getOrInsertFunction(functionName,
                                     Type::getInt32Ty(getGlobalContext()),
                                     Type::getInt32Ty(getGlobalContext()),
                                     0
                                    );
    assert( (function != 0) && "Could not insert function");
    assert( isa<Function>(function) && "FIXME: We don't want a bitcasted function");
    return cast<Function>(function);
  }

};
}

char ReplaceGetGlobalIDPass::ID = 0;
static RegisterPass<ReplaceGetGlobalIDPass> X("replace-get-global-id",
                                       "Replace all calls to get-global-id with something equivalent");

