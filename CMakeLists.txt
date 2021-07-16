cmake_minimum_required(VERSION 3.16)
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
        include/config-loader/deserialize/CompoundDeserializeTraits.h
        include/config-loader/deserialize/PrimitiveDeserializeTraits.h
        include/config-loader/deserialize/Deserializer.h
        include/config-loader/utils/Log.h
        include/config-loader/utils/Assertion.h
        src/utils/ConfigPath.cpp
        include/config-loader/parsers/TinyXML2Parser.h
        include/config-loader/parsers/JsonCppParser.h include/config-loader/parsers/YamlCppParser.h test/ut/YamlCppDeserializeTest.cpp)

add_library(config-loader STATIC
        ${CONFIG_LOADER_SRC})

add_executable(config_loader_test
        ${CONFIG_LOADER_SRC}
        test/ut/ReflectMacroTest.cpp
        test/ut/CatchMain.cpp
        test/ut/ReflectedStruct.h
        test/ut/TinyXML2Test.cpp
        test/ut/ConfigPathTest.cpp
        test/ut/TinyXML2DeserializeTest.cpp
        test/ut/DeserializableTest.cpp
        test/ut/ResultChecking.cpp
        test/ut/UtilsTest.cpp
        test/ut/JsonCppTest.cpp
        test/ut/JsonCppDeserializeTest.cpp
        test/ut/MixinDeserializeTest.cpp test/ut/DeserializeConfig.h test/ut/YamlCppTest.cpp)

target_link_libraries(config_loader_test PRIVATE Catch2::Catch2 tinyxml2::tinyxml2 jsoncpp_static yaml-cpp)

add_custom_target(copy_configs
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/test/ut/configs ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configs)
add_dependencies(config_loader_test copy_configs)
