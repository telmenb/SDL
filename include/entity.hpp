#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
public:
    Entity() = default;
    Entity(float dst_x, float dst_y, float src_x, float src_y, float src_w, float src_h, SDL_Texture* texture);
    float GetX() { return x; }
    float GetY() { return y; }
    SDL_Texture* GetTexture() { return texture_; }
    SDL_Rect GetFrame() { return current_frame_; }

private:
    const float x, y;
    SDL_Rect current_frame_;
    SDL_Texture* texture_;
};

#endif