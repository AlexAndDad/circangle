sugar_files (SOURCE_FILES
        Shaders.h Shaders.cpp)

sugar_files(SHADER_FILES FragmentShader.glsl VertexShader.glsl)
set_source_files_properties(${SHADER_FILES} PROPERTIES HEADER_FILE_ONLY 1)

foreach (sfile ${SHADER_FILES})
    get_filename_component(fname ${sfile} NAME)
    set(resobj "${PROJECT_BINARY_DIR}/Shaders/${fname}")
    sugar_files(SHADER_RESOURCES ${resobj})
    configure_file(${sfile} ${resobj} COPYONLY)
endforeach ()
