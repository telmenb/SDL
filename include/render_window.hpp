#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include "entity.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow {
public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* LoadTexture(const char* file_path);
	void CleanUp();
	void Clear();
	void Render(Entity& entity);
	void Display();
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
};

#endif