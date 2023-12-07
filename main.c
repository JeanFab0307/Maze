#include <stdio.h>
#include <SDL2/SDL.h>
#include "maze.h"

int init_instance(SDL_Instance *instance);
void init_player(SDL_Player *player, float X, float Y, float angle, float FOV);
/**
 * main - entry point in the program
 *
 * Return: 0 on success else 1
 */
int main(void)
{
	SDL_Instance instance;
	SDL_Player player;
	int map[ROWS][COLS] = {
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
				{1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
				{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };

	if (init_instance(&instance) !=0)
		return (1);
	init_player(&player, 6.0, 5.0, -PI / 2, PI / 3); /*the coordonates given are those in the maps*/

	while ("gg")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		if (poll_events(&player, map) == 1)
			break;
		draw_map(instance, map);
		draw_player(instance, &player);
		raycasting(instance, &player, map);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return(0);
}

/**
 * init_instance - initialize an SDL instance and checks for error
 * @instance: an instance that hold the address of the window and render
 * Return: 0 on success
 * Or 1 on error
 */
int init_instance(SDL_Instance *instance)
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s/n",
			SDL_GetError());
		return (1);
	}
	/* Create a new Window instance */
	instance->window = SDL_CreateWindow("SDL \\o/", SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED,
					    1260, 720, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* Create a new renderer instance linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_ACCELERATED |
						SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}

/**
 * init_player - initialize a player
 * @player: an instance of the player
 *
 * Return: Nothing
 */
void init_player(SDL_Player *player, float x, float y, float angle, float FOV)
{
	player->x = x * BOXSIZE + BOXSIZE / 2;
	player->y = y * BOXSIZE + BOXSIZE / 2;
	player->angle = angle;
	player->FOV = FOV;
}
