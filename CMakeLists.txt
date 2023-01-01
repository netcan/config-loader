cmake_minimum_required(VERSION 3.16)
project(config-loader)

set(CMAKE_CXX_STANDARD 17)

message(CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

option(BUILD_TESTS OFF)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
        set (BUILD_TESTS ON)
endif()

###############################################################################
# thirdparty option
option(HAS_TINYXML2 "enable tinyxml2" ON)
option(HAS_JSONCPP "enable jsoncpp" ON)
option(HAS_YAMLCPP "enable yamlcpp" ON)

message(STATUS "enable tinyxml2: ${HAS_TINYXML2}")
message(STATUS "enable jsoncpp: ${HAS_JSONCPP}")
message(STATUS "enable yamlcpp: ${HAS_YAMLCPP}")

###############################################################################

set(CONFIG_LOADER_INC
        include/config-loader/utils/RepeatMacro.h
        include/config-loader/core/DefineSchema.h
        include/config-loader/core/ReflectedTraits.h
        include/config-loader/ConfigLoaderNS.h
        include/config-loader/core/ForEachField.h
        include/config-loader/ConfigLoader.h
        include/config-loader/Result.h
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
        include/config-loader/parsers/UnsupportedParser.h
        include/config-loader/serialize/Serializer.h
        include/config-loader/serialize/SerializeTraits.h
        include/config-loader/serialize/SerializeTraitsDecl.h
        include/config-loader/utils/CommonTraits.h
        include/config-loader/serialize/PrimitiveSerializeTraits.h
        include/config-loader/serialize/CompoundSerializeTraits.h
        include/config-loader/serialize/TypeSerializer.h
        include/config-loader/utils/ConstexprStringUtils.h)

add_library(${PROJECT_NAME} STATIC
        ${CONFIG_LOADER_INC}
        src/utils/GetFileContent.cpp)

include(third-party/ThirdParty.cmake)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${THIRD_PARTY_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY include/config-loader DESTINATION include)


if (${BUILD_TESTS})
        add_subdirectory(test/ut)
endif()
