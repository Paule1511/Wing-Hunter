// Wing-Hunter.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include <iostream>
#include "SDL.h"
#undef main

using namespace std;

int main()
{
	cout << "Creating Window" << endl;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
	SDL_Delay(3000);
	return 0;
}
