cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0057 NEW)

project ("loadit")

# Добавьте источник в исполняемый файл этого проекта.
add_library(${PROJECT_NAME} SHARED _main.cpp VersionInfo.rc)

set(LIBRARY_OUTPUT_PATH ..\\)
