//
// Created by netcan on 2021/07/05.
//

#ifndef CONFIG_LOADER_DESERIALIZABLE_H
#define CONFIG_LOADER_DESERIALIZABLE_H
#include <config-loader/Result.h>
#include <config-loader/deserialize/DeserializeTraits.h>

CONFIG_LOADER_NS_BEGIN

template<typename T, typename FORMAT>
struct Deserializable {
    template<typename GET_CONTENT>
    Result load(T& obj, GET_CONTENT&& getContent) {
        return DeserializeTraits<FORMAT>::load(obj, getContent());
    }
};

CONFIG_LOADER_NS_END

#endif //CONFIG_LOADER_DESERIALIZABLE_H
