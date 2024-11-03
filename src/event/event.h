#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "event/key.h"

typedef enum {
    UNKNOWN_EVENT,
    WINDOW_CLOSE_EVENT,
    WINDOW_RESIZE_EVENT,
    KEY_PRESS_EVENT,
} EventType;

typedef struct {
    uint16_t width;
    uint16_t height;
} WindowResizeEventData;

typedef struct {
} WindowCloseEventData;

typedef struct {
    Keycode keycode;
} KeyPressEventData;

typedef struct {
    EventType type;
    bool handled;
    union {
        WindowResizeEventData window_resize;
        WindowCloseEventData window_close;
        KeyPressEventData key_press;
    };
} Event;
