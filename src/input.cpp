#include "input.hpp"


Input::Input() : pressed_key(NONE)
{
}

Input::~Input()
{
}

void Input::get_key_callback(int key, int scancode, int action, int mods)
{
    switch (key) {
    case 263:
        pressed_key = LEFT;
        break;
    case 262:
        pressed_key = RIGHT;
        break;
    case 265:
        pressed_key = UP;
        break;
    case 264:
        pressed_key = DOWN;
        break;
    }
}

KEY Input::return_key()
{
    return pressed_key;
}
