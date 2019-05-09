#include "window.h"
#include <SDL_image.h>
#include <iostream>

Window::Window(const string &title, int width, int height/*, const string& image_path*/) :_title(title), _width(width), _height(height)/*, _image_path(image_path)*/
{
	isRunning = init();
}


bool Window::init()
{
	//Checks if Video Initialization had no errors
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Failed to initalize Subsystems!..." << SDL_GetError() << endl;
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		cerr << "Failed to initalize SDL_image!" << IMG_GetError() << endl;
		return false;
	}
	//Creates Window
	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

	//Checks if Window Creation had no errors
	if (_window == NULL) {
		cerr << "Failed to create window! - WINDOW.CPP" << SDL_GetError() << endl;
		return 0;
	}

	//Creates Renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	//Checks if Renderer creation had no errors
	if (_renderer == NULL) {
		cerr << "Failed to create renderer! - WINDOW.CPP" << SDL_GetError() << endl;
		return 0;
	}
	/*
	//Creates background texture and frees surface used for creation
	SDL_Surface* surface = IMG_Load(_image_path.c_str());
	_background_texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_FreeSurface(surface);
	*/
	return true;
}

void Window::pollEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				isRunning = false;
				break;
			}
		default:
			break;
		}
	}
}

void Window::clear() const {
	//Renderer Properties
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
	//Background render
//	SDL_RenderCopy(_renderer, _background_texture, NULL, NULL);
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();
}