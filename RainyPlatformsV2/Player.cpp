#include "Player.h"
#include <SDL_image.h>

Player::Player(const Window& window, int width, int height, int x, int y, const string& image_path) :Window(window), _width(width), _height(height), _x(x), _y(y) {

	//Auto basically makes the var same type as return type of IMG_LOAD, same as SDL_Surface*
	SDL_Surface* surface = IMG_Load(image_path.c_str()); // <----- Can use auto surface here
	//Check for any errors
	try {
		//If surface wasn't created throw 1
		if (!surface) throw 1;
		//If it was then create player, then, if _player_texture wasn't created, throw 2
		else {
			_player_texture = SDL_CreateTextureFromSurface(Window::_renderer, surface);
			if (!_player_texture) throw 2;
		}
	}
	//Exception handling
	catch (int e) {
		if (e == 1)
			cerr << "Failed to create surface! - PLAYER.CPP" << endl;
		if (e == 2)
			cerr << "Failed to create texture! - PLAYER.CPP" << endl;
	}
	SDL_FreeSurface(surface);
	setRects(clipRect);
}

void Player::draw()
{

	player = { _x, _y, _width, _height };
	if (_player_texture) {
		SDL_RenderCopy(Window::_renderer, _player_texture, &clipRect[key], &player);
	}
	else {
		SDL_SetRenderDrawColor(Window::_renderer, _r, _g, _b, _a);
		SDL_RenderFillRect(Window::_renderer, &player);
	}
}

//This Function handles the keyboard states
void Player::keyboardHandler(timer& time) {
	if (state[SDL_SCANCODE_LEFT]) {
		if (!walkingR) {
			walkingL = true;
			key++;
			if (key == 31)
				key = 16;
			if (_x >= 0) {
				_x -= 1;
			}
			mapX += 2;
		}
	}
	if (state[SDL_SCANCODE_RIGHT]) {
		if (!walkingL) {
			walkingR = true;
			key++;
			if (key == 15 || key > 15)
				key = 0;
			if (_x <= 600) {
				_x += 1;
			}
			mapX -= 2;
		}
	}
	if (!state[SDL_SCANCODE_RIGHT]) {
		walkingR = false;
	}
	if (!state[SDL_SCANCODE_LEFT]) {
		walkingL = false;
	}
	if (state[SDL_SCANCODE_SPACE]) {
		jump(time);
	}
}
/*This function sets the rectangles that
will be used for difference frames of character animation*/
void Player::setRects(SDL_Rect* clip)
{
	clip[0] = { 0, 0, 89, 122 }; /*Facing right 1*/
	clip[1] = { 0, 0, 89, 122 }; /*Facing right 1*/
	clip[2] = { 0, 0, 89, 122 }; /*Facing right 1*/
	clip[3] = { 0, 0, 89, 122 }; /*Facing right 1*/

	clip[4] = { 0, 126, 94, 128 }; /*Facing right 2*/
	clip[5] = { 0, 126, 94, 128 }; /*Facing right 2*/
	clip[6] = { 0, 126, 94, 128 }; /*Facing right 2*/
	clip[7] = { 0, 126, 94, 128 }; /*Facing right 2*/

	clip[8] = { 0, 259, 89, 122 }; /*Facing right 3*/
	clip[9] = { 0, 259, 89, 122 }; /*Facing right 3*/
	clip[10] = { 0, 259, 89, 122 }; /*Facing right 3*/
	clip[11] = { 0, 259, 89, 122 }; /*Facing right 3*/

	clip[12] = { 0, 387, 89, 127 }; /*Facing right 4*/
	clip[13] = { 0, 387, 89, 127 }; /*Facing right 4*/
	clip[14] = { 0, 387, 89, 127 }; /*Facing right 4*/
	clip[15] = { 0, 387, 89, 127 }; /*Facing right 4*/

	clip[16] = { 121, 0, 89, 122 }; /*Facing left 1*/
	clip[17] = { 121, 0, 89, 122 }; /*Facing left 1*/
	clip[18] = { 121, 0, 89, 122 }; /*Facing left 1*/
	clip[19] = { 121, 0, 89, 122 }; /*Facing left 1*/

	clip[20] = { 116, 126, 94, 129 }; /*Facing left 2*/
	clip[21] = { 116, 126, 94, 129 }; /*Facing left 2*/
	clip[22] = { 116, 126, 94, 129 }; /*Facing left 2*/
	clip[23] = { 116, 126, 94, 129 }; /*Facing left 2*/

	clip[24] = { 121, 259, 89, 123 }; /*Facing left 3*/
	clip[25] = { 121, 259, 89, 123 }; /*Facing left 3*/
	clip[26] = { 121, 259, 89, 123 }; /*Facing left 3*/
	clip[27] = { 121, 259, 89, 123 }; /*Facing left 3*/

	clip[28] = { 121, 387, 89, 127 }; /*Facing left 4*/
	clip[29] = { 121, 387, 89, 127 }; /*Facing left 4*/
	clip[30] = { 121, 387, 89, 127 }; /*Facing left 4*/
	clip[31] = { 121, 387, 89, 127 }; /*Facing left 4*/
}

bool Player::check_collision(SDL_Rect A, SDL_Rect B) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	if (bottomA <= topB)
		return false;
	if (topA >= bottomB)
		return false;
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;
	return true;
}

void Player::jump(timer& time) {
	if (!isJumping) {
		isJumping = true;
		double deltaTime = time.get_deltaTime();
		currentForceJump = forceJump;
		player.y += currentForceJump * deltaTime;

		if (currentForceJump > fallSpeed)
			forceJump -= gravity * deltaTime;
		else
			currentForceJump = fallSpeed;

	}
	else {
		//Player is already jumping
		return;
	}
}

Player::~Player() {
	SDL_DestroyTexture(_player_texture);
	_player_texture = nullptr;
}