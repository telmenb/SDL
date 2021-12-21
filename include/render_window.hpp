#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include "entity.hpp"
#include "board.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 1700;
const int SCREEN_HEIGHT = 380;

class RenderWindow {
public:
	RenderWindow(const char* title, int width, int height);
	~RenderWindow();
	SDL_Texture* LoadTexture(const char* file_path);
	void Clear();
	void RenderEntities(Board& board);
	void Render(Entity& entity);
	void Display();
private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	SDL_Texture* stone_sprite_;
	SDL_Texture* board_texture_;
	std::vector<Entity> entities_;

	void ClearEntities();
	std::pair<float, float> SetDst(int idx);
	std::pair<float, float> SetSrc(int stones);
};

#endif