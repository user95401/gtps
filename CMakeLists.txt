
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

project ("SpeedDash")

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE curly-eureka ../curly-eureka/*.cpp)
file(GLOB_RECURSE src yo/*)
add_library(${PROJECT_NAME} SHARED ${curly-eureka} ${src})
target_include_directories(${PROJECT_NAME} PRIVATE
  ../curly-eureka/minhook/include
  ../curly-eureka/gd.h/include
  ../curly-eureka/gd.h
  ../curly-eureka
)
add_subdirectory(../curly-eureka/cocos-headers cocos-headers-build)
add_subdirectory(../curly-eureka/minhook minhook-build)
target_link_libraries(${PROJECT_NAME} minhook cocos2d)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
