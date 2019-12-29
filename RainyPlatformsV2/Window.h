#pragma once
#include <string>
#include <SDL.h>
using namespace std;

class Window
{
	//Initilization Method
	bool init();

	//Window Properties
	string _title;
	int _width;
	int _height;

	//Checks if window is closed or not
	bool isRunning = true;

	//Creates window and sets to null
	SDL_Window* _window = nullptr;

protected:
	SDL_Renderer* _renderer = nullptr;

public:

	Window(const string& title, int width, int height);
	~Window();

	inline bool running()const { return isRunning; }
	void pollEvents();
	void clear() const;
};