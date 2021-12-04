#include "render_window.hpp"

#include <iostream>

RenderWindow::RenderWindow(const char* title, int width, int height) 
								: window(nullptr), renderer(nullptr) {
	window = SDL_CreateWindow(  title,
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								width,
								height,
								0 );

	if (window == nullptr) 
        std::cout << "Error Initializing SDL_Window: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::LoadTexture(const char* file_path) {
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer, file_path);

	if (texture == nullptr)
		std::cout << "Error Loading Texture: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::Clear() {
	if ( SDL_RenderClear(renderer) != 0 )
		std::cout << "Error clearing render: " << SDL_GetError() << std::endl; 
}

void RenderWindow::Render(SDL_Texture* texture) {
	if ( SDL_RenderCopy(renderer, texture, nullptr, nullptr) != 0 )
		std::cout << "Error copying texture: " << SDL_GetError() << std::endl; 
}
	

void RenderWindow::Display() {
	SDL_RenderPresent(renderer);
}

void RenderWindow::CleanUp() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;
}
