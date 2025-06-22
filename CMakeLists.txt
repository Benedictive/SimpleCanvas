cmake_minimum_required(VERSION 4.0)

# set the project name and version
project(SimpleCanvas
        VERSION 0.2
        DESCRIPTION "A simple library to draw data to screen."
        LANGUAGES CXX)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

add_subdirectory(src)
