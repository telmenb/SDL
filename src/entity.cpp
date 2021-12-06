#include "entity.hpp"

Entity::Entity(float p_x, float p_y, float p_w, float p_h, SDL_Texture* texture)
                       : x(p_x), y(p_y), texture_(texture) {
    current_frame_.x = 0;
    current_frame_.y = 0;
    current_frame_.w = p_w;
    current_frame_.h = p_h;
}