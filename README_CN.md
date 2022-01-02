# config-loader
`config-loader`是一个使用C++17编写的 **解析配置文件** 到 **原生数据结构** 的静态反射框架，它拥有如下特点：

- 简单的接口，用户通过 **定义数据结构** 与提供对应的 **配置文件**，框架利用元编程技术生成 **读取** 接口
- 设计符合开闭原则，扩展 数据结构 无需修改框架
- 目前支持XML/JSON/YAML格式的配置文件，多种方式可以 **灵活组合**
- 轻量级，容易集成，核心代码不到1000行
- 支持 嵌套的数据结构、STL容器
- 测试用例完备
- 通过CMake选项来控制支持的格式

将来计划：

- 支持从原生数据结构写到配置文件、打印数据结构
- 提供额外的C++20版本

## 构建与运行
构建

```shell
$ git clone --depth=1 --recursive https://github.com/netcan/config-loader.git
$ cd config-loader
$ mkdir build
$ cd build
$ cmake ..
$ make -j
```

运行

```shell
$ cd bin/
$ ./config_loader_test
```

## 快速上手
使用 `DEFINE_SCHEMA` 定义数据结构：

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

提供配置文件，使用`loadXML2Obj/loadJSON2Obj/loadYAML2Obj`等接口：

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

又或者，通过XML配置文件。
```cpp
SomeOfPoints someOfPoints;
auto res = loadXML2Obj(someOfPoints, "configs/xml/SomeOfPoints.xml");
REQUIRE(res == Result::SUCCESS);
REQUIRE_THAT(someOfPoints.name, Equals("Some of points"));
REQUIRE(someOfPoints.points.size() == 3);
```

通过YAML配置文件。
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

## 注意事项
当前框架依赖如下几个库：
- `tinyxml2`，解析xml配置文件用
- `jsoncpp`，解析json配置文件用
- `yamlcpp`，解析yml配置文件用

将来可能通过CMake选项来使能这些库，避免在实际使用中产生不必要的依赖：只用xml就只依赖xml的解析库。

本框架需要配置文件按规范的格式提供。以XML为例，要求字段名与XML标签名对应，值与XML的文本内容对应；对于`map`数据结构，标签通过属性`name`作为Key名。

当前错误码语义。
```cpp
enum class Result {
    SUCCESS,              // 解析成功
    ERR_EMPTY_CONTENT,    // 解析文件为空
    ERR_ILL_FORMED,       // 解析文件非法
    ERR_MISSING_FIELD,    // 丢失字段
    ERR_EXTRACTING_FIELD, // 解析值失败
    ERR_TYPE,             // 类型错误
};
```
