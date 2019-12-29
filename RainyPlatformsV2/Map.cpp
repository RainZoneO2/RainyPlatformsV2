#include "Map.h"
using namespace std;

Map::Map(const Window& window, const string& image_path) : Window(window)
{
	Surf_Tileset = IMG_Load(image_path.c_str()); // <----- Can use auto surface here
	if (!Surf_Tileset)
		cerr << "Failed to create surface! - MAP.CPP" << endl;
	_tileset = SDL_CreateTextureFromSurface(_renderer, Surf_Tileset);
	if (!_tileset)
		cerr << "Failed to create texture! - MAP.CPP" << endl;
	SDL_FreeSurface(Surf_Tileset);
}

//This function load the .map into the vector TileList in order to render them, the .map file is in the format TileID :TypeID
bool Map::OnLoad(const char* File)
{
	TileList.clear();
	FILE* FileHandle = fopen(File, "r");

	try {
		if (!FileHandle) throw 1;
	}
	catch (int e) {
		if (e == 1)
			return false;
	}
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			Tile tempTile;
			//Read the file for the num:num to convert to tiles
			fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

			TileList.push_back(tempTile);
		}
		fscanf(FileHandle, "\n");
	}
	fclose(FileHandle);
	return true;
}

void Map::OnRender(int MapX, int MapY)
{
	if (_tileset == NULL)
		return;
	int w, h;
	SDL_QueryTexture(_tileset, NULL, NULL, &w, &h);
	int TilesetWidth = w / TILE_SIZE;
	int TilesetHeight = h / TILE_SIZE;

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].TypeID == TILE_TYPE_NONE) {
				ID++;
				continue;
			}
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
			int TilesetY = (TileList[ID].TileID / TilesetHeight) * TILE_SIZE;

			//Use these rects for the render copy {X,Y,H,W}
			SDL_Rect _SrcTile = { TilesetX, TilesetY, TILE_SIZE, TILE_SIZE };
			SDL_Rect _DstRect = { MapX + tX, MapY + tY, TILE_SIZE, TILE_SIZE };
			SDL_RenderCopy(_renderer, _tileset, &_SrcTile, &_DstRect);

			ID++;
		}
	}
}