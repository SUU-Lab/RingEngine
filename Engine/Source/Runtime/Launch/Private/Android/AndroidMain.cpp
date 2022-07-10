#include "Main.hpp"
#include <android/log.h>
#include <android_native_app_glue.h>
#include <thread>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

static std::mutex g_Mutex;
static bool g_AndroidExitRequested = false;
static std::thread::id g_AndroidEventThreadID;

bool IsAndroidEventThread()
{
    assert(g_AndroidEventThreadID != std::thread::id());
    return g_AndroidEventThreadID == std::this_thread::get_id();
}

//Touch and key input events
static int32_t AndroidHandleInputCB(struct android_app* app, AInputEvent* event)
{
    assert(IsAndroidEventThread());
    return 0;
}

//Lifetime events
static void AndroidOnAppCommandCB(struct android_app* app, int32_t cmd)
{
    assert(IsAndroidEventThread());

    switch (cmd)
    {
        case APP_CMD_SAVE_STATE:
            LOGI("APP_CMD_SAVE_STATE");
            break;

        case APP_CMD_INIT_WINDOW:
            LOGI("APP_CMD_INIT_WINDOW");
            break;

        case APP_CMD_TERM_WINDOW:
            LOGI("APP_CMD_TERM_WINDOW");
            {
                std::lock_guard<std::mutex> lockGuard(g_Mutex);
                g_AndroidExitRequested = true;
            }
            break;

        case APP_CMD_LOST_FOCUS:
            LOGI("APP_CMD_LOST_FOCUS");
            break;

        case APP_CMD_GAINED_FOCUS:
            LOGI("APP_CMD_GAINED_FOCUS");
            break;

        case APP_CMD_WINDOW_RESIZED:
            LOGI("APP_CMD_WINDOW_RESIZED");
            break;

        case APP_CMD_WINDOW_REDRAW_NEEDED:
            LOGI("APP_CMD_WINDOW_REDRAW_NEEDED");
            break;

        case APP_CMD_CONTENT_RECT_CHANGED:
            LOGI("APP_CMD_CONTENT_RECT_CHANGED");
            break;

        case APP_CMD_LOW_MEMORY:
            LOGI("APP_CMD_LOW_MEMORY");
            break;

        case APP_CMD_RESUME:
            LOGI("APP_CMD_RESUME");
            break;

        case APP_CMD_PAUSE:
            LOGI("APP_CMD_PAUSE");
            break;

        case APP_CMD_START:
            LOGI("APP_CMD_START");
            break;

        case APP_CMD_STOP:
            LOGI("APP_CMD_STOP");
            break;

        case APP_CMD_DESTROY:
            LOGI("APP_CMD_DESTROY");
            {
                std::lock_guard<std::mutex> lockGuard(g_Mutex);
                g_AndroidExitRequested = true;
            }
            break;
    }
}

static void AndroidProcessEvents(struct android_app* state)
{
    int fileDescriptor;
    int events;

    struct android_poll_source* source;
    while (ALooper_pollAll(-1, &fileDescriptor, &events, (void**)&source) >= 0)
    {
        if (source)
        {
            source->process(state, source);
        }
    }
}

static void AndroidEventThreadWorker(void* param)
{
    g_AndroidEventThreadID = std::this_thread::get_id();

    struct android_app* state = (struct android_app*)param;

    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    ALooper_addFd(looper, state->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, NULL,
                  &state->cmdPollSource);
    state->looper = looper;

    state->onInputEvent = AndroidHandleInputCB;
    state->onAppCmd = AndroidOnAppCommandCB;

    while (!g_AndroidExitRequested)
    {
        AndroidProcessEvents(state);

        std::this_thread::yield();
    }
}

void android_main(struct android_app* state)
{
    LOGI("android_main() is called.");

    std::thread androidEventThread(AndroidEventThreadWorker, state);
    androidEventThread.detach();

    ring::Main();

    while (!g_AndroidExitRequested)
    {}
}
