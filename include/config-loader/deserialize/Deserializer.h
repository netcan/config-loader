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
    Deserializer() = default;
    Deserializer(DESERIALIZABLE, DESERIALIZABLEs...) {}
    using DESERIALIZABLE::load;
    using DESERIALIZABLEs::load...;
};

template<typename DESERIALIZABLE, typename ...DESERIALIZABLEs> // C++17 deduction guide
Deserializer(DESERIALIZABLE, DESERIALIZABLEs...) -> Deserializer<DESERIALIZABLE, DESERIALIZABLEs...>;

// helper
template<typename T, typename FORMAT, typename CONFIG_CONTENT = decltype(""_path)>
constexpr auto AddItem(CONFIG_CONTENT) {
    return Deserializable<T, FORMAT, CONFIG_CONTENT>{};
}

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZER_H
