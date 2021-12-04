#include "render_window.hpp"

#include <iostream>

RenderWindow::RenderWindow(const char* title, int width, int height) 
								: window_(nullptr), renderer_(nullptr) {
	window_ = SDL_CreateWindow(  title,
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								width,
								height,
								0 );

	if (window_ == nullptr) 
        std::cout << "Error Initializing SDL_Window: " << SDL_GetError() << std::endl;

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::LoadTexture(const char* file_path) {
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer_, file_path);

	if (texture == nullptr)
		std::cout << "Error Loading Texture: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::Clear() {
	if ( SDL_RenderClear(renderer_) != 0 )
		std::cout << "Error clearing render: " << SDL_GetError() << std::endl; 
}

void RenderWindow::Render(Entity& entity) {

	SDL_Rect src;
	src.x = entity.GetFrame().x;
	src.y = entity.GetFrame().y;
	src.w = entity.GetFrame().w;
	src.h = entity.GetFrame().h;

	SDL_Rect dst;
	dst.x = entity.GetX() * 4;
	dst.y = entity.GetY() * 4;
	dst.w = entity.GetFrame().w * 4;
	dst.h = entity.GetFrame().h * 4;

	if ( SDL_RenderCopy(renderer_, entity.GetTexture(), &src, &dst) != 0 )
		std::cout << "Error copying texture: " << SDL_GetError() << std::endl; 
}
	

void RenderWindow::Display() {
	SDL_RenderPresent(renderer_);
}

void RenderWindow::CleanUp() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	renderer_ = nullptr;
	window_ = nullptr;
}
