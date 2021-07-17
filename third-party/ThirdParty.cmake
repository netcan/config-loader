add_subdirectory(third-party/Catch2)

if (HAS_TINYXML2)
add_subdirectory(third-party/tinyxml2)
endif()

if (HAS_JSONCPP)
add_subdirectory(third-party/jsoncpp)
endif()

if (HAS_YAMLCPP)
add_subdirectory(third-party/yaml-cpp)
endif()
