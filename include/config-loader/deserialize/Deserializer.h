//
// Created by netcan on 2021/07/07.
//

#ifndef CONFIG_LOADER_DESERIALIZER_H
#define CONFIG_LOADER_DESERIALIZER_H
#include <config-loader/deserialize/Deserializable.h>

CONFIG_LOADER_NS_BEGIN
// A deserializable composer(manager)
template<typename DESERIALIZABLE, typename ...DESERIALIZABLEs>
struct Deserializer // EBO
        : private DESERIALIZABLE
        , private DESERIALIZABLEs... {
    Deserializer() = default;
    Deserializer(DESERIALIZABLE, DESERIALIZABLEs...) {
        static_assert(sizeof(Deserializer) == 1); // empty obj check, stateless
    }
    using DESERIALIZABLE::load;
    using DESERIALIZABLEs::load...;
};

template<typename DESERIALIZABLE, typename ...DESERIALIZABLEs> // C++17 deduction guide
Deserializer(DESERIALIZABLE, DESERIALIZABLEs...) -> Deserializer<DESERIALIZABLE, DESERIALIZABLEs...>;

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZER_H
