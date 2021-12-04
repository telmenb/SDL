#include "entity.hpp"

Entity::Entity(float p_x, float p_y, SDL_Texture* texture)
                       : x(p_x), y(p_y), texture_(texture) {
    current_frame_.x = 0;
    current_frame_.y = 0;
    current_frame_.w = 32;
    current_frame_.h = 32;
}