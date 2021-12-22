#include "graphics.hpp"

#include <iostream>

Graphics::Graphics(const char* title, int width, int height) {
	window_ = SDL_CreateWindow(title,
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								width,
								height,
								0);
	if (window_ == nullptr) 
        std::cout << "Error Initializing SDL_Window: " << SDL_GetError() << std::endl;

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	large_font_ = TTF_OpenFont("res/ARCADE_N.TTF", 72);
	small_font_ = TTF_OpenFont("res/ARCADE_N.TTF", 36);
	board_texture_ = LoadTexture("res/board_b.png");
	stone_sprite_ = LoadTexture("res/stone_sprite.png");
}

SDL_Texture* Graphics::LoadTexture(const char* file_path) {
	SDL_Texture* texture = IMG_LoadTexture(renderer_, file_path);

	if (texture == nullptr)
		std::cout << "Error Loading Texture: " << SDL_GetError() << std::endl;

	return texture;
}

void Graphics::Clear() {
	if (SDL_RenderClear(renderer_) != 0)
		std::cout << "Error clearing render: " << SDL_GetError() << std::endl; 
}

void Graphics::RenderEntities(Board& board) {
	ClearEntities();

	//Rendering board and background
	entities_.push_back(Entity(0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, board_texture_));

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

void Graphics::RenderGameScore(Board& board) {
	//P1 score
	int w, h = 0;
	SDL_Rect rect;
	SDL_Surface* surface = TTF_RenderText_Solid(large_font_, std::to_string(board.AtIDX(6)).c_str(), {255, 255, 255});
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	if (board.AtIDX(6) < 10) {
		rect = {1670, 310, w, h};
	} else if (board.AtIDX(6) < 20) {
		rect = {1635, 310, w, h};
	} else {
		rect = {1640, 310, w, h};
	}

	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	//P2 score
	surface = TTF_RenderText_Solid(large_font_, std::to_string(board.AtIDX(13)).c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(renderer_, surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	if (board.AtIDX(13) < 10) {
		rect = {160, 310, w, h};
	} else if (board.AtIDX(13) < 20) {
		rect = {125, 310, w, h};
	} else {
		rect = {130, 310, w, h};
	}

	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Graphics::RenderGameText(Board& board) {
	//Player turn
	std::string turn;
	if (board.GetPlayerTurn() == Player::kPlayer1) {
		turn = "Player 1's turn";
	} else {
		turn = "Player 2's turn";
	}

	int w, h = 0;
	SDL_Surface* surface = TTF_RenderText_Solid(small_font_, turn.c_str(), {255, 255, 255});
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect rect = {(SCREEN_WIDTH - w) / 2, 580, w, h};

	SDL_RenderCopy(renderer_, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	//Mancala logo
	surface = TTF_RenderText_Solid(large_font_, "Mancala", {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(renderer_, surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	rect = {(SCREEN_WIDTH - w) / 2, 50, w, h};
	
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
			x = 345;
			break;
		case 1:
		case 11:
			x = 555;
			break;
		case 2:
		case 10:
			x = 765;
			break;
		case 3:
		case 9:
			x = 975;
			break;
		case 4:
		case 8:
			x = 1185;
			break;
		case 5:
		case 7:
			x = 1395;
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

void Graphics::ClearEntities() {
	entities_.clear();
}	

void Graphics::Display() {
	SDL_RenderPresent(renderer_);
}

bool Graphics::SplashScreen(SDL_Event* event) {
	SDL_Surface* large_surface = TTF_RenderText_Solid(large_font_, "Welcome to Mancala", {255, 255, 255});
	SDL_Surface* small_surface = TTF_RenderText_Solid(small_font_, "Click anywhere to start", {255, 255, 255});
	SDL_Texture* background_texture = LoadTexture("res/background.png");
	SDL_Texture* large_texture = SDL_CreateTextureFromSurface(renderer_, large_surface);
	SDL_Texture* small_texture = SDL_CreateTextureFromSurface(renderer_, small_surface);

	SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(renderer_, background_texture, NULL, &rect);

	int w, h = 0;
	SDL_QueryTexture(large_texture, NULL, NULL, &w, &h);
	rect = {(SCREEN_WIDTH - w) / 2, 280, w, h};
	SDL_RenderCopy(renderer_, large_texture, NULL, &rect);
	
	SDL_QueryTexture(small_texture, NULL, NULL, &w, &h);
	rect = {(SCREEN_WIDTH - w) / 2, 430, w, h};
	SDL_RenderCopy(renderer_, small_texture, NULL, &rect);

	Display();
	bool ready, quit = false;
	while (!ready) {
		while (SDL_PollEvent(event)) {
			if (event->type == SDL_QUIT) {
				ready = quit = true;
			}
			if (event->type == SDL_MOUSEBUTTONDOWN) {
				ready = true;
			}
		}
	}

	SDL_FreeSurface(large_surface);
	SDL_FreeSurface(small_surface);
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(large_texture);
	SDL_DestroyTexture(small_texture);
	Clear();

	return ready && !quit;
}

bool Graphics::EndScreen(SDL_Event* event, Board& board) {
	std::string winner_string;
	if (board.DeclareWinner() == Player::kPlayer1) winner_string = "Player 1 wins!";
	else if (board.DeclareWinner() == Player::kPlayer2) winner_string = "Player 2 wins!";
	else winner_string = "It's a Tie!";
	board.Reset();

	SDL_Surface* winner_surface = TTF_RenderText_Solid(large_font_, winner_string.c_str(), {255, 255, 255});
	SDL_Surface* replay_surface = TTF_RenderText_Solid(small_font_, "Click anywhere to start a new game", {255, 255, 255});
	SDL_Texture* background_texture = LoadTexture("res/background.png");
	SDL_Texture* winner_texture = SDL_CreateTextureFromSurface(renderer_, winner_surface);
	SDL_Texture* replay_texture = SDL_CreateTextureFromSurface(renderer_, replay_surface);

	SDL_Rect rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(renderer_, background_texture, NULL, &rect);

	int w, h = 0;
	SDL_QueryTexture(winner_texture, NULL, NULL, &w, &h);
	rect = {(SCREEN_WIDTH - w) / 2, 280, w, h};
	SDL_RenderCopy(renderer_, winner_texture, NULL, &rect);
	
	SDL_QueryTexture(replay_texture, NULL, NULL, &w, &h);
	rect = {(SCREEN_WIDTH - w) / 2, 430, w, h};
	SDL_RenderCopy(renderer_, replay_texture, NULL, &rect);

	Display();
	bool start, quit = false;
	while (!start) {
		while (SDL_PollEvent(event)) {
			if (event->type == SDL_QUIT) {
				start = quit = true;
			}
			if (event->type == SDL_MOUSEBUTTONDOWN) {
				start = true;
			}
		}
	}

	SDL_FreeSurface(winner_surface);
	SDL_FreeSurface(replay_surface);
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(winner_texture);
	SDL_DestroyTexture(replay_texture);
	Clear();

	return start && !quit;
}

Graphics::~Graphics() {
	SDL_DestroyTexture(stone_sprite_);
	SDL_DestroyTexture(board_texture_);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	TTF_CloseFont(large_font_);
	TTF_CloseFont(small_font_);
}
