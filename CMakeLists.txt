cmake_minimum_required(VERSION 3.16)
project(config_loader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

message(CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

###############################################################################
# thirdparty option
option(HAS_TINYXML2 "enable tinyxml2" ON)
option(HAS_JSONCPP "enable jsoncpp" ON)
option(HAS_YAMLCPP "enable yamlcpp" ON)

message(STATUS "enable tinyxml2: ${HAS_TINYXML2}")
message(STATUS "enable jsoncpp: ${HAS_JSONCPP}")
message(STATUS "enable yamlcpp: ${HAS_YAMLCPP}")

include(third-party/ThirdParty.cmake)
###############################################################################

set(CONFIG_LOADER_INC
        include/config-loader/utils/RepeatMacro.h
        include/config-loader/core/DefineSchema.h
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
        include/config-loader/parsers/TinyXML2Parser.h
        include/config-loader/parsers/JsonCppParser.h
        include/config-loader/parsers/YamlCppParser.h
        include/config-loader/parsers/UnsupportedParser.h)

add_library(config-loader STATIC
        ${CONFIG_LOADER_INC}
        src/utils/ConfigPath.cpp)

target_include_directories(config-loader
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS config-loader DESTINATION lib)
install(DIRECTORY include/config-loader DESTINATION include)

add_subdirectory(test/ut)