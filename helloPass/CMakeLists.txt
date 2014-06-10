copy_files_to_build_dir(*.c *.md)
add_library(SRGHello MODULE Hello.cpp)

get_property(MODULE_FILE TARGET SRGHello PROPERTY LOCATION)
configure_file(run.sh.in run.sh @ONLY)
