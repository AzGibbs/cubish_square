#include "input.hpp"


Input::Input() : pressed_key(NONE)
{
}

Input::~Input()
{
}

void Input::get_key_callback(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_LEFT:
            pressed_key = LEFT;
            break;
        case GLFW_KEY_RIGHT:
            pressed_key = RIGHT;
            break;
        case GLFW_KEY_UP:
            pressed_key = UP;
            break;
        case GLFW_KEY_DOWN:
            pressed_key = DOWN;
            break;
        }
    }
    else if (action == GLFW_REPEAT) {

    }
    else {
        pressed_key = NONE;
    }
}

KEY Input::return_key()
{
    return pressed_key;
}
