copy_files_to_build_dir(*.c *.md)

file(GLOB shell_scripts "*.sh.in")
foreach (file ${shell_scripts})
    get_filename_component(script_name  "${file}" NAME_WE)
    configure_file("${script_name}.sh.in" "${script_name}.sh" @ONLY)
endforeach()
