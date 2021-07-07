//
// Created by netcan on 2021/07/07.
//

#ifndef CONFIG_LOADER_DESERIALIZER_H
#define CONFIG_LOADER_DESERIALIZER_H
#include <config-loader/deserialize/Deserializable.h>

CONFIG_LOADER_NS_BEGIN
template<typename DESERIALIZABLE, typename ...DESERIALIZABLEs>
struct Deserializer
        : private DESERIALIZABLE
        , private DESERIALIZABLEs... {
    using DESERIALIZABLE::load;
    using DESERIALIZABLEs::load...;
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZER_H
