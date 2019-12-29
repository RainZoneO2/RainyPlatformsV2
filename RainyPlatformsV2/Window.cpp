#include "window.h"
#include <SDL_image.h>
#include <iostream>

Window::Window(const string& title, int width, int height) :_title(title), _width(width), _height(height)/*, _image_path(image_path)*/
{
	isRunning = init();
}


bool Window::init()
{
	//Checks if Video Initialization had no errors
	try {
		//If SDL_Init returns an error
		if (SDL_Init(SDL_INIT_VIDEO) != 0) throw 1;

		//If IMG_Init returns an error
		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) throw 2;
	}
	//Exception management
	catch (int e) {
		if (e == 1) {
			cerr << "Failed to initalize Subsystems!..." << SDL_GetError() << endl;
			return false;
		}
		if (e == 2) {
			cerr << "Failed to initalize SDL_image!" << IMG_GetError() << endl;
			return false;
		}
	}
	//Creates Window
	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

	//Checks if Window Creation had no errors
	try {
		//If _window has still not been created, throw 3
		if (_window == NULL) throw 3;
	}
	//Exception management
	catch (int e) {
		if (e == 3) {
			cerr << "Failed to create window! - WINDOW.CPP" << SDL_GetError() << endl;
			return 0;
		}
	}

	//Creates Renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	//Checks if Renderer creation had no errors
	try {
		//If _renderer has still not been created, throw 4
		if (_renderer == NULL) throw 4;
	}
	//Exception management
	catch (int e) {
		if (e == 4) {
			cerr << "Failed to create renderer! - WINDOW.CPP" << SDL_GetError() << endl;
			return 0;
		}
	}
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
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();
}