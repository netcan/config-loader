//
// Created by netcan on 2021/07/09.
//

#ifndef CONFIG_LOADER_ASSERTION_H
#define CONFIG_LOADER_ASSERTION_H

#define CFL_EXPECT_SUCC(call) do {                  \
    if (auto res = call; res != Result::SUCCESS) {  \
        return res;                                 \
    }                                               \
} while(0)                                          \

#endif //CONFIG_LOADER_ASSERTION_H
