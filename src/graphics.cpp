#include "graphics.hpp"

#include <iostream>

Graphics::Graphics(const char* title, int width, int height) 
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

	font_ = TTF_OpenFont("res/ARCADE_N.TTF", 72);

	board_texture_ = LoadTexture("res/board.png");

	stone_sprite_ = LoadTexture("res/stone_sprite.png");
}

SDL_Texture* Graphics::LoadTexture(const char* file_path) {
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer_, file_path);

	if (texture == nullptr)
		std::cout << "Error Loading Texture: " << SDL_GetError() << std::endl;

	return texture;
}

void Graphics::Clear() {
	if ( SDL_RenderClear(renderer_) != 0 )
		std::cout << "Error clearing render: " << SDL_GetError() << std::endl; 
}

void Graphics::RenderEntities(Board& board) {
	ClearEntities();

	entities_.push_back(Entity(0, (SCREEN_HEIGHT - BOARD_HEIGHT) / 2, 0, 0, BOARD_WIDTH, BOARD_HEIGHT, board_texture_));

	for (int i = 0; i < 13; i++) {
		if (i == 6 || i == 13) continue;
		std::pair<float, float> dst = SetStoneDst(i);
		std::pair<float, float> src = SetStoneSrc(board.AtIDX(i));
		entities_.push_back(Entity(dst.first, dst.second, src.first, src.second, STONE_WIDTH, STONE_HEIGHT, stone_sprite_));
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

void Graphics::RenderScore(Board& board) {
	SDL_Surface* surface = TTF_RenderText_Solid(font_, std::to_string(board.AtIDX(6)).c_str(), {255, 255, 255});
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
	int w, h = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect rect;
	if (board.AtIDX(6) < 10) {
		rect = {1570, 310, w, h};
	} else {
		rect = {1535, 310, w, h};
	}
	SDL_RenderCopy(renderer_, texture, NULL, &rect);

	surface = TTF_RenderText_Solid(font_, std::to_string(board.AtIDX(13)).c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(renderer_, surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	if (board.AtIDX(13) < 10) {
		rect = {60, 310, w, h};
	} else {
		rect = {25, 310, w, h};
	}
	SDL_RenderCopy(renderer_, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

std::pair<float, float> Graphics::SetStoneDst(int idx) {
	float x, y = 0;
	if (idx < 6) {
			y = 360;
		} else {
			y = 180;
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

std::pair<float, float> Graphics::SetStoneSrc(int stones) {
	float x, y = 0;
	switch (stones) {
		case 0:
			x = 160;
			y = 160 * 2;
			break;
		case 1:
			x = 0;
			y = 0;
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
			x = 0;
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

void Graphics::Render(Entity& entity) {

	SDL_Rect src = entity.GetFrame();

	SDL_Rect dst = entity.GetFrame();
	dst.x = entity.GetX();
	dst.y = entity.GetY();

	if ( SDL_RenderCopy(renderer_, entity.GetTexture(), &src, &dst) != 0 )
		std::cout << "Error copying texture: " << SDL_GetError() << std::endl; 
}

void Graphics::ClearEntities() {
	entities_.clear();
}
	

void Graphics::Display() {
	SDL_RenderPresent(renderer_);
}

Graphics::~Graphics() {
	SDL_DestroyTexture(stone_sprite_);
	SDL_DestroyTexture(board_texture_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	TTF_CloseFont(font_);
	font_ = nullptr;
	renderer_ = nullptr;
	window_ = nullptr;
	stone_sprite_ = nullptr;
	board_texture_ = nullptr;
}
