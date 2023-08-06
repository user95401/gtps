cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

project ("gtps")

#curly-eureka
file(GLOB_RECURSE curly-eureka-src ../curly-eureka/*.cpp)
set(curly-eureka-incl ../curly-eureka/minhook/include ../curly-eureka/gd.h/include ../curly-eureka/gd.h ../curly-eureka)
add_subdirectory(../curly-eureka/cocos-headers cocos-headers-build)
add_subdirectory(../curly-eureka/minhook minhook-build)

# Add the source to the executable file of this project.
file(GLOB_RECURSE src_main yo/*)
file(GLOB_RECURSE src_layers yo/layers/*)
add_library(${PROJECT_NAME} SHARED ${src_main} ${src_layers} ${curly-eureka-src})
target_include_directories(${PROJECT_NAME} PRIVATE ${curly-eureka-incl}
yo
yo/layers
)
target_link_libraries(${PROJECT_NAME} minhook cocos2d)

set(LIBRARY_OUTPUT_PATH "D:\\Games\\user666\\Gemetry_Trash_Private_Servero_v1.5\\gtps")
