#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "board.hpp"

#include <SDL2/SDL.h>

class Mouse {
    public:
        Mouse();
        int GetPocketNum(SDL_Event* event);
        
    private:
        int x_pos, y_pos;
};


#endif