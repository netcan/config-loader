//
// Created by netcan on 2021/07/04.
//

#ifndef CONFIG_LOADER_DESERIALIZEXMLCONFIG_H
#define CONFIG_LOADER_DESERIALIZEXMLCONFIG_H

namespace xml_config {
constexpr auto POINT_CONFIG = R"(
<?xml version="1.0" encoding="UTF-8"?>
<point>
    <x>1.2</x>
    <y>3.4</y>
</point>
)";

constexpr auto RECT_CONFIG = R"(
<?xml version="1.0" encoding="UTF-8"?>
<rect>
    <p1>
        <x>1.2</x>
        <y>3.4</y>
    </p1>
    <p2>
        <x>5.6</x>
        <y>7.8</y>
    </p2>
    <color>0x12345678</color>
</rect>
)";

constexpr auto SOME_OF_POINTS_CONFIG = R"(
<?xml version="1.0" encoding="UTF-8"?>
<some_of_points>
    <name>Some of points</name>
    <points>
        <value>
            <x>1.2</x>
            <y>3.4</y>
        </value>
        <value>
            <x>5.6</x>
            <y>7.8</y>
        </value>
        <value>
            <x>2.2</x>
            <y>3.3</y>
        </value>
    </points>
</some_of_points>
)";
}

#endif //CONFIG_LOADER_DESERIALIZEXMLCONFIG_H
