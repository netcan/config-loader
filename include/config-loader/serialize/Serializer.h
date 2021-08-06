//
// Created by netcan on 2021/08/06.
//

#ifndef CONFIG_LOADER_SERIALIZER_H
#define CONFIG_LOADER_SERIALIZER_H
#include <config-loader/serialize/SerializeTraits.h>
CONFIG_LOADER_NS_BEGIN
template<typename T>
void dumpObj2OStream(std::ostream& out, const T& obj) {
    CompoundSerializeTraits<T>::dump(out, obj);
}
CONFIG_LOADER_NS_END
#endif //CONFIG_LOADER_SERIALIZER_H
