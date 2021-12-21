#include "mouse.hpp"

Mouse::Mouse() {
    y_pos = x_pos = 0;
}

int Mouse::GetPocketNum(SDL_Event* event) {
    SDL_GetMouseState(&x_pos, &y_pos);

    if (y_pos >= 20 && y_pos <= 180) {
        //Top row
        if (x_pos >= 245 && x_pos <= 405) return 12;
        if (x_pos >= 455 && x_pos <= 615) return 11;
        if (x_pos >= 665 && x_pos <= 825) return 10;
        if (x_pos >= 875 && x_pos <= 1035) return 9;
        if (x_pos >= 1085 && x_pos <= 1245) return 8;
        if (x_pos >= 1295 && x_pos <= 1455) return 7;
    } else if (y_pos >= 200 && y_pos <= 360) {
        //Bottom row
        if (x_pos >= 245 && x_pos <= 405) return 0;
        if (x_pos >= 455 && x_pos <= 615) return 1;
        if (x_pos >= 665 && x_pos <= 825) return 2;
        if (x_pos >= 875 && x_pos <= 1035) return 3;
        if (x_pos >= 1085 && x_pos <= 1245) return 4;
        if (x_pos >= 1295 && x_pos <= 1455) return 5;
    }
    return 13;
}