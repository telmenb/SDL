#include "entity.hpp"

Entity::Entity(float dst_x, float dst_y, float src_x, float src_y, SDL_Texture* texture)
                                               : x(dst_x), y(dst_y), texture_(texture) {
    current_frame_.x = src_x;
    current_frame_.y = src_y;
    current_frame_.w = 160;
    current_frame_.h = 160;
}

//Special constructor for Board entity
Entity::Entity(float p_x, float p_y, float p_w, float p_h, float src_x, float src_y, SDL_Texture* texture)
                                                                    : x(p_x), y(p_y), texture_(texture) {
    current_frame_.x = 0;
    current_frame_.y = 0;
    current_frame_.w = p_w;
    current_frame_.h = p_h;
}