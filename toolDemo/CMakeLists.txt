add_executable(tool tool.cpp)

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(tool ${llvm_libs})
