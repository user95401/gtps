cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /MANIFEST:NO")
cmake_policy(SET CMP0057 NEW)

project ("gtps")
set(developer "user95401")
set(version "v1.6.0")
set(description "Main mod for Gemetry Trash Private Servero")
set(repository "https://github.com/user95401/gtps")
set(issues_url "https://discord.gg/k2uTDUvNRg")
set(issues_info "U can write about it on <cb>gtps discord server.</c>")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}") # dll output
set(GEODE_MOD_OUTPUT_PATH "D:\\Games\\user666\\Gemetry_Trash_Private_Servero_v1.6\\geode\\mods") # geode mod output

#curly-eureka
include("C:\\Users\\Lenovo\\source\\curly-eureka\\CURLY-EUREKA-INCL.cmake")

# Add the source to the executable file of this project.
file(GLOB_RECURSE src_main 
yo/*
yo/layers/*
yo/objects/*
)
add_library(${PROJECT_NAME} SHARED ${src_main} ${curly_eureka_src})
target_include_directories(${PROJECT_NAME} PRIVATE
yo
yo/layers
yo/objects
)

#geode-makeup
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/geode geode-build)

#ARCHIVE-MOD
if(EXISTS ${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.dll)
    file(ARCHIVE_CREATE
        OUTPUT "${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.zip"
        PATHS 
            about.md
            #changelog.md
            #Resources
            ${developer}.${PROJECT_NAME}.dll
        FORMAT "zip")
endif()