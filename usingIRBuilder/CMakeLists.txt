copy_files_to_build_dir(*.cl *.md)
add_library(ReplaceGetGlobalID MODULE ReplaceGetGlobalID.cpp)

get_property(MODULE_FILE TARGET ReplaceGetGlobalID PROPERTY LOCATION)
configure_file(run.sh.in run.sh @ONLY)
