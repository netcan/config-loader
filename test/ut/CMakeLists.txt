add_executable(config_loader_test
        ReflectMacroTest.cpp
        UTSchema.h
        UtilsTest.cpp
        DeserializerTest.cpp
        ResultChecking.cpp
        TinyXML2Test.cpp
        TinyXML2DeserializeTest.cpp
        JsonCppTest.cpp
        JsonCppDeserializeTest.cpp
        YamlCppDeserializeTest.cpp
        YamlCppTest.cpp
        DeserializeConfig.h
        SerializerTest.cpp TypeSerializerTest.cpp ConstexprStringTest.cpp)

set_target_properties(
        config_loader_test
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(config_loader_test PRIVATE config-loader Catch2WithMain ${THIRD_PARTY_LIBRARIES})

add_custom_target(copy_configs
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/configs ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configs)

add_dependencies(config_loader_test copy_configs)
