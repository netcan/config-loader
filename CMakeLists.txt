cmake_minimum_required(VERSION 3.19)
project(config_loader VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(config-loader STATIC
        include/config-loader/RepeatMacro.h
        include/config-loader/DefineStruct.h)

add_executable(ReflectStruct examples/ReflectStruct.cpp)
#target_link_libraries(ReflectStruct config-loader)