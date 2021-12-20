#include "render_window.hpp"

#include <iostream>

RenderWindow::RenderWindow(const char* title, int width, int height) 
								: window_(nullptr), renderer_(nullptr) {
	window_ = SDL_CreateWindow(title,
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								width,
								height,
								0);

	if (window_ == nullptr) 
        std::cout << "Error Initializing SDL_Window: " << SDL_GetError() << std::endl;

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	board_texture_ = LoadTexture("res/board.png");

	stone_sprite_ = LoadTexture("res/stone_sprite.png");
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

void RenderWindow::RenderEntities(Board& board) {
	ClearEntities();

	entities_.push_back(Entity(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, board_texture_)); //special constructor

	for (int i = 0; i < 13; i++) {
		if (i == 6 || i == 13) continue;
		std::pair<float, float> dst = SetDst(i);
		std::pair<float, float> src = SetSrc(board.AtIDX(i));
		entities_.push_back(Entity(dst.first, dst.second, src.first, src.second, stone_sprite_));
	}

	for (int i = 0; i < entities_.size(); i++) {
		SDL_Rect src = entities_.at(i).GetFrame();

		SDL_Rect dst = entities_.at(i).GetFrame();
		dst.x = entities_.at(i).GetX();
		dst.y = entities_.at(i).GetY();

		if ( SDL_RenderCopy(renderer_, entities_.at(i).GetTexture(), &src, &dst) != 0 )
			std::cout << "Error copying texture: " << SDL_GetError() << std::endl;
	}
}

std::pair<float, float> RenderWindow::SetDst(int idx) {
	float x, y = 0;
	if (idx < 6) {
			y = 200;
		} else {
			y = 20;
		}

	switch (idx) {
		case 0:
		case 12:
			x = 245;
			break;
		case 1:
		case 11:
			x = 455;
			break;
		case 2:
		case 10:
			x = 665;
			break;
		case 3:
		case 9:
			x = 875;
			break;
		case 4:
		case 8:
			x = 1085;
			break;
		case 5:
		case 7:
			x = 1295;
			break;
	}
	return std::make_pair(x, y);
}

std::pair<float, float> RenderWindow::SetSrc(int stones) {
	float x, y = 0;
	switch (stones) {
		case 0:
			x = 160;
			y = 160 * 2;
			break;
		case 1:
			break;
		case 2:
			x = 160;
			break;
		case 3:
			x = 160 * 2;
			break;
		case 4:
			x = 160 * 3;
			break;
		case 5:
			x = 160 * 4;
			break;
		case 6:
			y = 160;
			break;
		case 7:
			x = 160;
			y = 160;
			break;
		case 8:
			x = 160 * 2;
			y = 160;
			break;
		case 9:
			x = 160 * 3;
			y = 160;
			break;
		case 10:
			x = 160 * 4;
			y = 160;
			break;
		default:
			x = 0;
			y = 160 * 2;
	}
	return std::make_pair(x, y);
}

void RenderWindow::Render(Entity& entity) {

	SDL_Rect src = entity.GetFrame();

	SDL_Rect dst = entity.GetFrame();
	dst.x = entity.GetX();
	dst.y = entity.GetY();

	if ( SDL_RenderCopy(renderer_, entity.GetTexture(), &src, &dst) != 0 )
		std::cout << "Error copying texture: " << SDL_GetError() << std::endl; 
}

void RenderWindow::ClearEntities() {
	entities_.clear();
}
	

void RenderWindow::Display() {
	SDL_RenderPresent(renderer_);
}

void RenderWindow::CleanUp() {
	SDL_DestroyTexture(stone_sprite_);
	SDL_DestroyTexture(board_texture_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	renderer_ = nullptr;
	window_ = nullptr;
	stone_sprite_ = nullptr;
	board_texture_ = nullptr;
}
