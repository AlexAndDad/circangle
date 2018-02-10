if (DEFINED TargetOptions_Included)
    return()
endif ()
set(TargetOptions_Included 1)

macro(AllWarnings TARGET)

    set(opts)

    set(decent 0)
    set(shite 0)

    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        set(decent 1)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(decent 1)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        set(decent 1)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set(shite 1)
    endif ()

    if (decent)
        list(APPEND opts -Wreturn-type)
    endif ()

    if (shite)
    endif ()

    foreach (opt IN LISTS opts)
        target_compile_options(${TARGET} PUBLIC ${opt})
    endforeach ()
endmacro()

macro(SetDefaultSource TARGET)
    target_compile_definitions(${TARGET} PUBLIC "_DEFAULT_SOURCE=1")
endmacro()
