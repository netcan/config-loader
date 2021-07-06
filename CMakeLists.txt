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
        include/config-loader/ForEachField.h
        include/config-loader/Deserializable.h
        include/config-loader/ConfigLoader.h
        include/config-loader/Result.h include/config-loader/PathString.h include/config-loader/DeserializeTraitsDecl.h include/config-loader/DeserializeTraits.h include/config-loader/TinyXML2DeserializeTraits.h)

add_library(config-loader STATIC
        ${CONFIG_LOADER_SRC})

add_executable(config_loader_test
        ${CONFIG_LOADER_SRC}
        test/ut/DeserializeXMLConfig.h
        test/ut/ReflectMacroTest.cpp
        test/ut/CatchMain.cpp
        test/ut/ReflectedStruct.h test/ut/TinyXML2Test.cpp test/ut/PathStringTest.cpp test/ut/TinyXML2DeserializeTest.cpp)

target_link_libraries(config_loader_test PRIVATE Catch2::Catch2 tinyxml2::tinyxml2)
