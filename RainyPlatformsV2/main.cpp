#include <SDL.h>
#include <stdio.h>
#include "Map.h"
#include "Window.h"
#include "Player.h"
#include "timer.h"
#include "Define.h"
#include "Camara.h"

const int FRAMES_PER_SECOND = 30;

int main(int argc, char* argv[]) {
	/*Create the window(Title, Width, Height)*/
	Window window("Rainy Platforms", WWIDTH, WHEIGHT);

	/*Create the map(Window, Image)*/
	Map map(window, "Assets/tileset.png");

	/*Load .map for rendering*/
	map.OnLoad("Assets/Maps/1.map");

	/*Create character(window, Width, Height, XPos, YPos, Image)*/
	Player character(window, 45, 60, 100, 355, "Assets/Player/charSheet.png");

	/*Create timer*/
	timer FPS;

	/*Create camara*/
	Camara camara;

	/*Game loop for the all class methods and such*/
	while (window.running()) {

		/*Starts timer*/
		FPS.start();
		/*Handle keyboard inputs for player*/
		character.keyboardHandler(FPS);
		/*Poll window events*/
		window.pollEvents();
		/*Render map and scroll*/
		map.OnRender(character.mapX, 0);
		/*Draw character*/
		character.draw();
		/*Clear window for next loop iteration*/
		window.clear();

		//Modify FPS based on performance and DeltaTime
		if (FPS.get_ticks() < 1000 / FRAMES_PER_SECOND)
			SDL_Delay((1000 / FRAMES_PER_SECOND) - FPS.get_ticks());
	}

	return 0;
}