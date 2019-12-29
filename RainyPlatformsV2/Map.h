#pragma once
#include <SDL.h>
#include <vector>
#include <sstream>
#include <SDL_image.h>
#include <iostream>
#include "Tile.h"
#include "Window.h"
#pragma warning(disable : 4996)

class Map : public Window
{
	std::vector<Tile> TileList;
	SDL_Texture* _tileset = nullptr;
	SDL_Surface* Surf_Tileset;
public:
	Map(const Window& window, const string& image_path);

	bool OnLoad(const char* File);
	void OnRender(int MapX, int MapY);
};