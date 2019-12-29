#pragma once
#include "Window.h"
#include "timer.h"
#include "Define.h"
#include <string>
#include <iostream>
using namespace std;

class Player : public Window
{
	//The player attributes
	int _width, _height;
	int _x, _y;
	int _r, _g, _b, _a;

	//Jump Related Attributes
	float fallSpeed = -5.0f;
	float forceJump = 5.0f;
	float currentForceJump = 0.0f;
	float gravity = 0.2f;

	//The texture the player will use
	SDL_Texture* _player_texture = nullptr;

	//Player Rectangle
	SDL_Rect player = { 0, 0, 0, 0 };

	//Rectangle used for clipping
	SDL_Rect clipRect[32];

	//Integer used as frame key for animation
	int key = 0;

	//Used for Keyboard state (Anti-Ghosting Solution)
	const Uint8* state = SDL_GetKeyboardState(NULL);

	//The bool var that will update depending on the player jump status
	bool isJumping = false;

	//Bool variables used so player cannot walk left and right at the same time
	bool walkingL = false;
	bool walkingR = false;

public:
	Player(const Window& window, int width, int height, int x, int y, const string& image_path);
	~Player();

	//Draw character to screen
	void draw();

	/*This function takes to rects and compares
	their x-y values to decide whether they
	are colliding or not.*/
	bool check_collision(SDL_Rect A, SDL_Rect B);

	//Function used for jumping
	void jump(timer& time);

	//Function for handling keyboard inputs
	void keyboardHandler(timer& time);

	//Function to clip sprite sheet to individual characters
	void setRects(SDL_Rect* clip);
	//Variable used for map positon
	int mapX = 0;
};