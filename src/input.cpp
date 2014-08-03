#include "input.hpp"


Input::Input() : pressed_key {NONE}
{
h_keys.left = UNPRESSED;
h_keys.right = UNPRESSED;
h_keys.up = UNPRESSED;
h_keys.down = UNPRESSED;
prime_keys = {NONE, NONE};
}

Input::~Input()
{
}

void Input::get_key_callback(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        std::cout<<"PRESS"<<std::endl;
        switch (key) {
        case GLFW_KEY_LEFT:
 //           std::cout<<"LEFT"<<std::endl;
            prime_keys.h = LEFT;
            h_keys.left = PRESSED;
            break;
        case GLFW_KEY_RIGHT:
 //           std::cout<<"RIGHT"<<std::endl;
            prime_keys.h = RIGHT;
            h_keys.right = PRESSED;
            break;
        case GLFW_KEY_UP:
 //           std::cout<<"UP"<<std::endl;
            prime_keys.v = UP;
            h_keys.up = PRESSED;
            break;
        case GLFW_KEY_DOWN:
 //           std::cout<<"DOWN"<<std::endl;
            prime_keys.v = DOWN;
            h_keys.down = PRESSED;
            break;
        }
    }
    else if (action == GLFW_REPEAT) {
        
    }
    else {
       // pressed_key = NONE;
        switch (key) {
        case GLFW_KEY_LEFT:
            h_keys.left = UNPRESSED;
            if (h_keys.right == PRESSED) {
                prime_keys.h = RIGHT;
            }
            else {
                prime_keys.h = NONE;
            }
            break;
        case GLFW_KEY_RIGHT:
            h_keys.right = UNPRESSED;
            if (h_keys.left == PRESSED) {
                prime_keys.h = LEFT;
            }
            else {
                prime_keys.h = NONE;
            }
            break;
        case GLFW_KEY_UP:
            h_keys.up = UNPRESSED;
            if (h_keys.down == PRESSED) {
                prime_keys.v = DOWN;
            }
            else {
                prime_keys.v = NONE;
            }
            break;
        case GLFW_KEY_DOWN:
            h_keys.down = UNPRESSED;
            if (h_keys.up == PRESSED) {
                prime_keys.v = UP;
            }
            else {
                prime_keys.v = NONE;
            }
            break;
 
        } 
    }
}

struct Input::PrimeKeys Input::return_key()
{//   std::cout<<h_keys.left<<" "<<h_keys.right<<" "<<h_keys.up<<" "<<h_keys.down<<std::endl;
//    std::cout<<prime_keys.h<<" "<<prime_keys.v<<std::endl;
    return prime_keys;
}
