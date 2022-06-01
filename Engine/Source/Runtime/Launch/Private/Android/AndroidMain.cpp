﻿#include "Main.hpp"
#include <android/log.h>
#include <android_native_app_glue.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

void android_main(struct android_app* state)
{
    LOGI("android_main() is called.");

    ring::Main();
}
