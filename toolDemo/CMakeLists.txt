add_executable(tool tool.cpp)

target_link_libraries(tool LLVMSupport LLVMCore LLVMIRReader)
