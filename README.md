# config-loader [中文版](README_CN.md)
`config-loader` is a static reflection framework written in C++17 from **parse configuration file** to **native data structure**. It has the following characteristics:

- Simple interface, users need to **define data structure** and provide corresponding **configuration file**, the framework uses meta-programming technology to generate **load** interface
- The design conforms to the opening and closing principle, extends the data structure without modifying the framework
- Currently supports XML and Json format configuration files, a variety of methods can be **flexibly composed**
- Lightweight, easy to integrate, less than ~1000 lines of code
- Support nested data structure, STL container
- Complete test cases

Future plans:
- Support Yaml configuration file
- Enable the supported formats through CMake options
- Provide additional C++20 version

## Get started quickly
Firstly use `DEFINE_STRUCT` macro to define the data structure:

```cpp
// define and reflect a struct
DEFINE_STRUCT(Point,                          // struct Point {
              (double) x,                     //     double x;
              (double) y);                    //     double y;
                                              // };

// vector and string
DEFINE_STRUCT(SomeOfPoints,                   // struct SomeOfPoints {
              (std::string) name,             //     std::string name;
              (std::vector<Point>) points);   //     std::vector<Point> points;
                                              // };
```

Provide configuration files, load on demand:

```cpp
SomeOfPoints someOfPoints;
auto res = JsonLoader<SomeOfPoints>().load(someOfPoints, [] {
    return R"(
        {
            "name": "Some of points",
            "points":[
                {"x": 1.2, "y": 3.4 },
                {"x": 5.6, "y": 7.8 },
                {"x": 2.2, "y": 3.3}
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
auto res = XMLLoader<SomeOfPoints>().load(someOfPoints, [] {
    return R"(
        <?xml version="1.0" encoding="UTF-8"?>
        <some_of_points>
            <name>Some of points</name>
            <points>
                <value><x>1.2</x><y>3.4</y></value>
                <value><x>5.6</x><y>7.8</y></value>
                <value><x>2.2</x><y>3.3</y></value>
            </points>
        </some_of_points>
    )";
});
REQUIRE(res == Result::SUCCESS);
REQUIRE_THAT(someOfPoints.name, Equals("Some of points"));
REQUIRE(someOfPoints.points.size() == 3);
```

Sometimes, your software system needs a unified configuration management module to manage all data structures and corresponding configuration files. At this time, you can define the manager by composing each `Loader`.

```cpp
inline Deserializer ConfigLoaderManager(
    JsonLoader<Point>("/etc/configs/Point.json"_path),
    XMLLoader<Rect>("/etc/configs/Rect.xml"_path),
    JsonLoader<SomeOfPoints>() // Provide config file on demand
);
```

Similarly, use the `load` interface to load on demand, and `ConfigLoaderManager` will automatically parse it according to the configured path and the given data structure. Your IDE should be able to get all the `load` interfaces.

```text
 82     Deserializer ConfigLoaderManager(
 83             JsonLoader<Point>(),
 84             XMLLoader<Rect>(),
 85             JsonLoader<SomeOfPoints>()
 86     );
 87     ConfigLoaderManager.l
 88                         load(Rect &obj)~                                   f [LS]
 89                         load(Point &obj)~                                  f [LS]
 90 }                       load(SomeOfPoints &obj, GET_CONTENT &&getContent)~ f [LS]
~                           load(SomeOfPoints &obj)~                           f [LS]
~                           load(Rect &obj, GET_CONTENT &&getContent)~         f [LS]
~                           load(Point &obj, GET_CONTENT &&getContent)~        f [LS]
```

## Notice
The current framework depends on the following two library:
- `tinyxml2`, used for parsing xml configuration files
- `jsoncpp`, used for parsing json configuration files

In the future, these libraries may be enabled through CMake options to avoid unnecessary dependencies in actual use: only using xml will only rely on the xml parsing library.

This framework requires configuration files to be provided in a standardized format. Taking XML as an example, the field name is required to correspond to the XML tag name, and the value corresponds to the text content of the XML; for the `map` data structure, the tag uses the attribute `name` as the key name.

The semantics of the current error code.
```cpp
enum class Result {
    SUCCESS,              // parse successfully
    ERR_EMPTY_CONTENT,    // The parsing file is empty
    ERR_ILL_FORMED,       // Illegal parsing file
    ERR_MISSING_FIELD,    // Missing field
    ERE_EXTRACTING_FIELD, // Failed to parse the value
    ERR_TYPE,             // Type error
};
```
