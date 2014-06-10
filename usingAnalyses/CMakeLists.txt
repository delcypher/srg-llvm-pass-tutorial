copy_files_to_build_dir(*.c *.md)
add_library(CycleDetect MODULE CycleDetect.cpp)

get_property(MODULE_FILE TARGET CycleDetect PROPERTY LOCATION)
configure_file(run.sh.in run.sh @ONLY)
