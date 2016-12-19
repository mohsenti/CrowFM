macro(COPY_FILES target source_dir target_dir)
    file(GLOB _files RELATIVE ${source_dir} "${source_dir}/*.*")
    foreach(FILENAME ${_files})
        set(source_file ${source_dir}/${FILENAME})
        set(target_file ${target_dir}/${FILENAME})
            add_custom_command(
                    TARGET ${target}
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${source_file}" "${target_file}"
                    VERBATIM
            )
    endforeach()
endmacro()

