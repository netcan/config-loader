cmake_minimum_required(VERSION 3.17)
project(config_loader)

set(CMAKE_CXX_STANDARD 17)

include(third-party/ThirdParty.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CONFIG_LOADER_SRC
        include/config-loader/utils/RepeatMacro.h
        include/config-loader/core/DefineStruct.h
        include/config-loader/core/ReflectedTraits.h
        include/config-loader/ConfigLoaderNS.h
        include/config-loader/core/ForEachField.h
        include/config-loader/deserialize/Deserializable.h
        include/config-loader/ConfigLoader.h
        include/config-loader/Result.h
        include/config-loader/utils/ConfigPath.h
        include/config-loader/deserialize/DeserializeTraitsDecl.h
        include/config-loader/deserialize/DeserializeTraits.h
        include/config-loader/deserialize/tinyxml2/TinyXML2DeserializeTraits.h
        include/config-loader/deserialize/CommonDeserializeTraits.h
        include/config-loader/deserialize/Deserializer.h
        include/config-loader/utils/Log.h
        include/config-loader/utils/Assertion.h
        src/utils/ConfigPath.cpp include/config-loader/deserialize/tinyxml2/TinyXML2Adapter.h)

add_library(config-loader STATIC
        ${CONFIG_LOADER_SRC})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test/ut/configs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_executable(config_loader_test
        ${CONFIG_LOADER_SRC}
        test/ut/DeserializeXMLConfig.h
        test/ut/ReflectMacroTest.cpp
        test/ut/CatchMain.cpp
        test/ut/ReflectedStruct.h test/ut/TinyXML2Test.cpp test/ut/ConfigPathTest.cpp test/ut/TinyXML2DeserializeTest.cpp test/ut/DeserializableTest.cpp test/ut/ResultChecking.cpp test/ut/UtilsTest.cpp test/ut/DeserializeJsonCppConfig.h test/ut/JsonCppTest.cpp)

target_link_libraries(config_loader_test PRIVATE Catch2::Catch2 tinyxml2::tinyxml2 jsoncpp_static)
