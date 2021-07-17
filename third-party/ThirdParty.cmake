add_subdirectory(third-party/Catch2)

if (HAS_TINYXML2)
add_compile_definitions(HAS_TINYXML2)
add_subdirectory(third-party/tinyxml2)
list(APPEND THIRD_PARTY_LIBRARIES tinyxml2::tinyxml2)
endif()

if (HAS_JSONCPP)
add_compile_definitions(HAS_JSONCPP)
add_subdirectory(third-party/jsoncpp)
list(APPEND THIRD_PARTY_LIBRARIES jsoncpp_static)
endif()

if (HAS_YAMLCPP)
add_compile_definitions(HAS_YAMLCPP)
add_subdirectory(third-party/yaml-cpp)
list(APPEND THIRD_PARTY_LIBRARIES yaml-cpp)
endif()