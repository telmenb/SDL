#include "entity.hpp"

Entity::Entity(float dst_x, float dst_y, float src_x, float src_y, float src_w, float src_h, SDL_Texture* texture)
                                                                    : x(dst_x), y(dst_y), texture_(texture) {
    current_frame_.x = src_x;
    current_frame_.y = src_y;
    current_frame_.w = src_w;
    current_frame_.h = src_h;
}