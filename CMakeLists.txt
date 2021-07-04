cmake_minimum_required(VERSION 3.19)
project(config_loader)

set(CMAKE_CXX_STANDARD 17)

include(cmake/ThirdParty.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CONFIG_LOADER_SRC
        include/config-loader/RepeatMacro.h
        include/config-loader/DefineStruct.h
        include/config-loader/ReflectedTraits.h
        include/config-loader/ConfigLoaderNS.h
        include/config-loader/ForEachField.h include/config-loader/ConfigLoader.h)

add_library(config-loader STATIC
        ${CONFIG_LOADER_SRC})

add_executable(config_loader_test
        ${CONFIG_LOADER_SRC}
        test/ut/DeserializeXMLConfig.h
        test/ut/ReflectMacroTest.cpp
        test/ut/CatchMain.cpp
        test/ut/ReflectedStruct.h)

target_link_libraries(config_loader_test PRIVATE Catch2::Catch2)
