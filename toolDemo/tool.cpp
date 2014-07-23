// vim: set sw=2 ts=2 expandtab softtabstop=2:
#include "llvm/IR/LLVMContext.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Assembly/Parser.h"
#include "llvm/IR/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/SystemUtils.h"
#include <memory>

using namespace llvm;

static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input .ll or .bc file>"), cl::init("-"));
static cl::opt<bool>
DisableVerify("disable-verify", cl::Hidden,
              cl::desc("Do not run verifier on input LLVM (dangerous!)"));


int main(int argc, char **argv) {
  // Print a stack trace if we signal out.
  sys::PrintStackTraceOnErrorSignal();
  PrettyStackTraceProgram X(argc, argv);
  LLVMContext &Context = getGlobalContext();
  llvm_shutdown_obj Y;  // Call llvm_shutdown() on exit.
  cl::ParseCommandLineOptions(argc, argv, "Demo tool\n");

  // Parse the file now...
  // Guess the file type from extension
  std::unique_ptr<Module> M;
  SMDiagnostic Err;
  if (StringRef(InputFilename).endswith(".ll")) {
    // Parse as LLVM Assembly
    M.reset(ParseAssemblyFile(InputFilename, Err, Context));
    if (M.get() == 0) {
      Err.print(argv[0], errs(), /*showColors=*/ true);
      return 1;
    }
  }
  else if (StringRef(InputFilename).endswith(".bc")) {
    // Parse as LLVM bitcode
    M.reset(ParseIRFile(InputFilename, Err, Context));
    if (M.get() == 0) {
      Err.print(argv[0], errs(), /*showColors=*/ true);
      return 1;
    }
  }
  else {
    errs() << "Input file has unsupported extension\n";
    return 1;
  }

  if (!DisableVerify) {
    std::string Err;
    if (verifyModule(*M.get(), &errs() )) {
      errs() << "Assembly parsed, but does not verify a correct\n";
      return 1;
    }
  }

  errs() << "Here's the assembly:\n" << *M.get();

  return 0;
}

