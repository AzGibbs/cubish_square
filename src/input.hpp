#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>
#include <iostream>

enum KEY {NONE, LEFT, RIGHT, UP, DOWN};


class Input {
KEY pressed_key;

public:
    Input();
    ~Input();
    
    void get_key_callback(int key, int scancode, int action, int mods);
    
    KEY return_key();
};

#endif
