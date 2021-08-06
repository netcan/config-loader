//
// Created by netcan on 2021/08/06.
//

#ifndef CONFIG_LOADER_COMMONTRAITS_H
#define CONFIG_LOADER_COMMONTRAITS_H
#include <config-loader/ConfigLoaderNS.h>
CONFIG_LOADER_NS_BEGIN
namespace detail {
template<bool support>
struct IsSupport {
    static constexpr bool isSupport = support;
};
}
CONFIG_LOADER_NS_END
#endif //CONFIG_LOADER_COMMONTRAITS_H
