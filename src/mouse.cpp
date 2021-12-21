#include "mouse.hpp"

Mouse::Mouse() {
    y_pos = x_pos = 0;
}

int Mouse::GetPocketNum(SDL_Event* event) {
    SDL_GetMouseState(&x_pos, &y_pos);

    //Top row
    if (y_pos >= 180 && y_pos <= 340) {
        if (x_pos >= 345 && x_pos <= 505) return 12;
        if (x_pos >= 555 && x_pos <= 715) return 11;
        if (x_pos >= 765 && x_pos <= 925) return 10;
        if (x_pos >= 975 && x_pos <= 1135) return 9;
        if (x_pos >= 1185 && x_pos <= 1345) return 8;
        if (x_pos >= 1395 && x_pos <= 1555) return 7;
    //Bottom row
    } else if (y_pos >= 360 && y_pos <= 520) {
        if (x_pos >= 345 && x_pos <= 505) return 0;
        if (x_pos >= 555 && x_pos <= 715) return 1;
        if (x_pos >= 765 && x_pos <= 925) return 2;
        if (x_pos >= 975 && x_pos <= 1135) return 3;
        if (x_pos >= 1185 && x_pos <= 1345) return 4;
        if (x_pos >= 1395 && x_pos <= 1555) return 5;
    }
    return 13;
}