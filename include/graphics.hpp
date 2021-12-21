#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "entity.hpp"
#include "board.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 1700;
const int SCREEN_HEIGHT = 700;
const int BOARD_WIDTH = 1700;
const int BOARD_HEIGHT = 380;
const int STONE_WIDTH = 160;
const int STONE_HEIGHT = 160;

class Graphics {
public:
	Graphics(const char* title, int width, int height);
	~Graphics();
	SDL_Texture* LoadTexture(const char* file_path);
	void Clear();
	void RenderEntities(Board& board);
	void RenderScore(Board& board);
	void Render(Entity& entity);
	void Display();
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	TTF_Font* font_;
	SDL_Texture* stone_sprite_;
	SDL_Texture* board_texture_;
	std::vector<Entity> entities_;

	void ClearEntities();
	std::pair<float, float> SetStoneDst(int idx);
	std::pair<float, float> SetStoneSrc(int stones);
};

#endif