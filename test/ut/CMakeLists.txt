add_executable(config_loader_test
        ReflectMacroTest.cpp
        CatchMain.cpp
        ReflectedStruct.h
        TinyXML2Test.cpp
        ConfigPathTest.cpp
        TinyXML2DeserializeTest.cpp
        DeserializableTest.cpp
        ResultChecking.cpp
        UtilsTest.cpp
        JsonCppTest.cpp
        JsonCppDeserializeTest.cpp
        YamlCppDeserializeTest.cpp
        MixinDeserializeTest.cpp
        DeserializeConfig.h
        YamlCppTest.cpp)

target_link_libraries(config_loader_test PRIVATE config-loader Catch2::Catch2 ${THIRD_PARTY_LIBRARIES})

add_custom_target(copy_configs
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/configs ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configs)

add_dependencies(config_loader_test copy_configs)
