#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>
#include <iostream>

enum class Key {none, left, right, up, down};
enum class State {unpressed, pressed};

class Input {
Key pressed_key;
struct {State left, right, up, down;} h_keys;

public:
    Input();
    ~Input();
    
    void get_key_callback(int key, int scancode, int action, int mods);
    
    struct PrimeKeys {Key h, v;} prime_keys;
    struct PrimeKeys return_key();
};

#endif
