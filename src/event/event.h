#pragma once

#include <stdint.h>

#include "event/key.h"
#include "event/mouse.h"

typedef enum {
    UNKNOWN_EVENT,
    WINDOW_CLOSE_EVENT,
    WINDOW_RESIZE_EVENT,
    KEY_PRESS_EVENT,
    MOUSE_BUTTON_PRESS_EVENT,
    CUSTOM_EVENT,
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
  MouseButton button; 
} MouseButtonPressEventData;

typedef struct {
    int16_t type;
    union {
        WindowResizeEventData window_resize;
        WindowCloseEventData window_close;
        KeyPressEventData key_press;
        MouseButtonPressEventData mouse_button_press;
    };
} Event;
