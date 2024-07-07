cmake_minimum_required(VERSION 3.12)

# set the project name and version
project(SimpleCanvas
        VERSION 0.1
        DESCRIPTION "A simple library to draw data to screen."
        LANGUAGES CXX)

# specify the C++ standard
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

add_subdirectory(src)

#include_directories("${PROJECT_SOURCE_DIR}/../../Libraries/SDL2-2.30.4/include")
#link_directories("${PROJECT_SOURCE_DIR}/../../Libraries/SDL2-2.30.4/lib/x64")

#set(SRC_SUBDIR "src/")

#list(TRANSFORM SRC_FILES PREPEND ${SRC_SUBDIR})

#add_library(SimpleCanvas
#    ${SRC_FILES}
#)

#target_link_libraries(SimpleCanvas PRIVATE SDL2main SDL2)