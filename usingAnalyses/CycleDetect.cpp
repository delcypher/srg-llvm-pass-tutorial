/* This code is taken from [Bugle](https://github.com/mc-imperial/bugle)
 * with a few modifications. See LICENCE
 */
#include "llvm/Pass.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct CycleDetectPass : public ModulePass {

  static char ID;
  CycleDetectPass() : ModulePass(ID) { }

  bool runOnModule(llvm::Module &M) override {
    CallGraph &CG = getAnalysis<CallGraphWrapperPass>().getCallGraph();
    scc_iterator<CallGraph *> i = scc_begin(&CG), e = scc_end(&CG);
    bool hasCycle = false;
    while (i != e) {
      if (i.hasLoop()) {
        errs().changeColor(raw_ostream::RED, /*bold=*/true, /*bg=*/false);
        errs() << "A cycle was detected in the call graph!\n";
        hasCycle = true;

        auto nodes = *i;
        errs() << "The following functions were involved in the cycle\n\n";
        errs().changeColor(raw_ostream::RED, /*bold=*/false, /*bg=*/false);
        for (CallGraphNode* node : nodes)
            node->print(errs());

        errs().resetColor();
      }
      ++i;
    }

    if (!hasCycle) {
        errs().changeColor(raw_ostream::GREEN, /*bold=*/true, /*bg=*/false);
        errs() << "No cycle was detected in the call graph\n";
        errs().resetColor();
    }

    return false;
  }

  virtual const char *getPassName() const {
    return "CallGraph cycle detection";
  }

  virtual void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.setPreservesAll();

    // We are explicitly stating that we require this analysis
    AU.addRequired<llvm::CallGraphWrapperPass>();
  }
};
}

char CycleDetectPass::ID = 0;
static RegisterPass<CycleDetectPass> X("cycle-detect",
                                       "Detect if there is a cycle in the call graph");

