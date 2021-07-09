//
// Created by netcan on 2021/07/09.
//

#ifndef CONFIG_LOADER_LOG_H
#define CONFIG_LOADER_LOG_H
#include <cstdio>

#define LOGI(fmt, ...) printf("[ConfigLoader] I " fmt "\n", ##__VA_ARGS__)
#define LOGE(fmt, ...) printf("[ConfigLoader] E " fmt "\n", ##__VA_ARGS__)

#endif //CONFIG_LOADER_LOG_H
