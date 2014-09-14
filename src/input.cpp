#include "input.hpp"


Input::Input() : pressed_key{Key::none}
{
    h_keys.left = State::unpressed;
    h_keys.right = State::unpressed;
    h_keys.up = State::unpressed;
    h_keys.down = State::unpressed;
    prime_keys = {Key::none, Key::none};
}

Input::~Input()
{
}


// TODO refactor
void Input::get_key_callback(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        std::cout << "PRESS" << std::endl;
        switch (key) {
        case GLFW_KEY_LEFT:
 //           std::cout<<"LEFT"<<std::endl;
            prime_keys.h = Key::left;
            h_keys.left = State::pressed;
            break;
        case GLFW_KEY_RIGHT:
 //           std::cout<<"RIGHT"<<std::endl;
            prime_keys.h = Key::right;
            h_keys.right = State::pressed;
            break;
        case GLFW_KEY_UP:
 //           std::cout<<"UP"<<std::endl;
            prime_keys.v = Key::up;
            h_keys.up = State::pressed;
            break;
        case GLFW_KEY_DOWN:
 //           std::cout<<"DOWN"<<std::endl;
            prime_keys.v = Key::down;
            h_keys.down = State::pressed;
            break;
        }
    } else if (action == GLFW_REPEAT) {
        
    } else {
       // pressed_key = NONE;
        switch (key) {
        case GLFW_KEY_LEFT:
            h_keys.left = State::unpressed;
            if (h_keys.right == State::pressed)
                prime_keys.h = Key::right;
            else
                prime_keys.h = Key::none;
            break;
        case GLFW_KEY_RIGHT:
            h_keys.right = State::unpressed;
            if (h_keys.left == State::pressed)
                prime_keys.h = Key::left;
            else
                prime_keys.h = Key::none;
            break;
        case GLFW_KEY_UP:
            h_keys.up = State::unpressed;
            if (h_keys.down == State::pressed)
                prime_keys.v = Key::down;
            else
                prime_keys.v = Key::none;
            break;
        case GLFW_KEY_DOWN:
            h_keys.down = State::unpressed;
            if (h_keys.up == State::pressed)
                prime_keys.v = Key::up;
            else
                prime_keys.v = Key::none;
            break;
 
        } 
    }
}


struct Input::PrimeKeys Input::return_key()
{    
    return prime_keys;
}
