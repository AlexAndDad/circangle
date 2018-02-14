sugar_include(Texture\ Loader)


sugar_files(TEXTURE_FILES awesomeface.png container.jpg)
set_source_files_properties(${TEXTURE_FILES} PROPERTIES HEADER_FILE_ONLY 1)

foreach (sfile ${TEXTURE_FILES})
    get_filename_component(fname ${sfile} NAME)
    set(resobj "${PROJECT_BINARY_DIR}/Textures/${fname}")
    sugar_files(TEXTURE_RESOURCES ${resobj})
    configure_file(${sfile} ${resobj} COPYONLY)
endforeach ()
