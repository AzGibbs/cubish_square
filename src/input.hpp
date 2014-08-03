#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>
#include <iostream>

enum KEY {NONE, LEFT, RIGHT, UP, DOWN};
enum STATE {UNPRESSED, PRESSED};

class Input {
KEY pressed_key;
struct {STATE left, right, up, down;} h_keys;
public:
    Input();
    ~Input();
    
    void get_key_callback(int key, int scancode, int action, int mods);
    
    struct PrimeKeys {KEY h, v;} prime_keys;
    struct PrimeKeys return_key();
};

#endif
