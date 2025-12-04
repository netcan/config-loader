//
// This project is a personal hobby work. The author hereby assigns all
// intellectual property rights in this project to Huawei Technologies Co., Ltd.,
// and imposes no obligations or liabilities on Huawei.
//
// 本项目为作者个人业余创作，作者在此声明将本项目及其衍生作品相关的全部知识产权无偿
// 转让给华为技术有限公司，且不对华为提出任何义务或责任要求。
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
