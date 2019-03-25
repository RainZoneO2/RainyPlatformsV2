#include "Texture.h"

Texture::Texture()
{
	//Initialize
	_Texture = NULL;
	_Width = 0;
	_Height = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		//newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_Width = loadedSurface->w;
			_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	_Texture = newTexture;
	return _Texture != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if (_Texture != NULL)
	{
		SDL_DestroyTexture(_Texture);
		_Texture = NULL;
		_Width = 0;
		_Height = 0;
	}
}

void Texture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, _Width, _Height };
	//SDL_RenderCopy(_renderer, mTexture, NULL, &renderQuad);
}

int Texture::getWidth()
{
	return _Width;
}

int Texture::getHeight()
{
	return _Height;
}