# config-loader [中文版](README_CN.md)
`config-loader` is a static reflection framework written in C++17 from **parse configuration file** to **native data structure**. It has the following characteristics:

- Simple interface, users need to **define data structure** and provide corresponding **configuration file**, the framework uses meta-programming technology to generate **load** interface
- The design conforms to the opening and closing principle, extends the data structure without modifying the framework
- Currently supports XML, JSON and YAML format configuration files, a variety of methods can be **flexibly composed**
- Lightweight, easy to integrate, less than ~1000 lines of code
- Support nested data structure, STL container
- Complete test cases
- Support from native data structure to config file, stringify data structure

Future plans:

- Provide additional C++20 version

## Build & Run
Build

```shell
$ git clone --recursive https://github.com/netcan/config-loader.git
$ cd config-loader
$ mkdir build
$ cd build
$ cmake ..
$ make -j
```

Run

```shell
$ cd bin/
$ ./config_loader_test
```

## Quickly start

Firstly use `DEFINE_SCHEMA` macro to define the data structure:

```cpp
// define and reflect a struct
DEFINE_SCHEMA(Point,                          // struct Point {
              (double) x,                     //     double x;
              (double) y);                    //     double y;
                                              // };

// vector and string
DEFINE_SCHEMA(SomeOfPoints,                   // struct SomeOfPoints {
              (std::string) name,             //     std::string name;
              (std::vector<Point>) points);   //     std::vector<Point> points;
                                              // };
```

Provide configuration files, using `loadXML2Obj/loadJSON2Obj/loadYAML2Obj` interfaces:

```cpp
SomeOfPoints someOfPoints;
auto res = loadJSON2Obj(someOfPoints, [] {
    return R"(
        {
            "name": "Some of points",
            "points":[
                { "x": 1.2, "y": 3.4 },
                { "x": 5.6, "y": 7.8 },
                { "x": 2.2, "y": 3.3 }
            ]
        }
    )";
});
REQUIRE(res == Result::SUCCESS);
REQUIRE_THAT(someOfPoints.name, Equals("Some of points"));
REQUIRE(someOfPoints.points.size() == 3);
```

Or, through an XML configuration file.
```cpp
SomeOfPoints someOfPoints;
auto res = loadXML2Obj(someOfPoints, "configs/xml/SomeOfPoints.xml");
REQUIRE(res == Result::SUCCESS);
REQUIRE_THAT(someOfPoints.name, Equals("Some of points"));
REQUIRE(someOfPoints.points.size() == 3);
```

Through a YAML configuration file.
```cpp
SomeOfPoints someOfPoints;
auto res = loadYAML2Obj(someOfPoints, [] {
return R"(
        name: Some of points
        points:
          - x: 1.2
            y: 3.4
          - x: 5.6
            y: 7.8
          - x: 2.2
            y: 3.3
    )";
});
REQUIRE(res == Result::SUCCESS);
REQUIRE_THAT(someOfPoints.name, Equals("Some of points"));
REQUIRE(someOfPoints.points.size() == 3);
```

## Notice
The current framework depends on the following libraries:
- `tinyxml2`, used for parsing xml configuration files
- `jsoncpp`, used for parsing json configuration files
- `yamlcpp`, used for parsing yaml configuration files

In the future, these libraries may be enabled through CMake options to avoid unnecessary dependencies in actual use: only using xml will only rely on the xml parsing library.

This framework requires configuration files to be provided in a standardized format. Taking XML as an example, the field name is required to correspond to the XML tag name, and the value corresponds to the text content of the XML; for the `map` data structure, the tag uses the attribute `name` as the key name.

The semantics of the current error code.
```cpp
enum class Result {
    SUCCESS,              // parse successfully
    ERR_EMPTY_CONTENT,    // The parsing file is empty
    ERR_ILL_FORMED,       // Illegal parsing file
    ERR_MISSING_FIELD,    // Missing field
    ERR_EXTRACTING_FIELD, // Failed to parse the value
    ERR_TYPE,             // Type error
};
```
