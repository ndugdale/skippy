#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>

#ifndef NDEBUG
#define LOG_DEBUG(...) SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define LOG_INFO(...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define LOG_WARN(...) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define LOG_ERROR(...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)
#define ASSERT(condition, ...)  \
    if (!(condition)) {         \
        LOG_ERROR(__VA_ARGS__); \
        abort();                \
    }
#else
#define LOG_TRACE(x)
#define LOG_INFO(x)
#define LOG_WARN(x)
#define LOG_ERROR(x)
#define LOG_FATAL(x)
#define ASSERT(condition, x)
#endif
