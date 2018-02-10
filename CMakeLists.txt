cmake_minimum_required(VERSION 3.0)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/polly/cxx17.cmake")
endif ()


list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(HunterGate)

HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.20.5.tar.gz"
        SHA1 "9f5eb722cbd9068f3d21a43b07832f8cc41336a1"
)

project(CircAngle)
hunter_add_package(sugar)
find_package(sugar CONFIG REQUIRED)

set(program_name circangle)

sugar_files(SOURCE_FILES main.cpp)
add_executable(${program_name} ${SOURCE_FILES})

include(AddBoost)
#AddBoost(TARGETS ${program_name} PRIVATE COMPONENTS system)

if (NOT glm_DIR)
    hunter_add_package(glm)
endif ()
find_package(glm CONFIG REQUIRED)
target_link_libraries(${program_name} PUBLIC glm)

hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)
target_link_libraries(${program_name} PUBLIC glew::glew)

hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${program_name} PUBLIC glfw)

#warnings
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    include(TargetOptions)
    AllWarnings(${program_name})
endif ()
SetDefaultSource(${program_name})
