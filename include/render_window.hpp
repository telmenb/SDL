#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class RenderWindow {
public:
	RenderWindow(const char* title, int width, int height);
	SDL_Texture* LoadTexture(const char* file_path);
	void CleanUp();
	void Clear();
	void Render(SDL_Texture* texture);
	void Display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif