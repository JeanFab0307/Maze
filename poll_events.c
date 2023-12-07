#include <SDL2/SDL.h>
#include <math.h>
#include "maze.h"

int no_collision(SDL_Player *player, int map[ROWS][COLS], int x, int y);

/**
 * poll_events - retrieve events
 *
 * Return: 1 if the action is meant to exit the program
 * Or 0 for other actions
 */
int poll_events(SDL_Player *player, int map[ROWS][COLS])
{
	SDL_Event event;
	SDL_KeyboardEvent key;
	float paceX = 0, paceY = 0;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			switch (key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				return (1);
			case SDL_SCANCODE_W:
				paceX = 2 * cos(player->angle);
				paceY = 2 * sin(player->angle);
				break;
			case SDL_SCANCODE_S:
				paceX = 2 * cos(player->angle - PI);
				paceY = 2 * sin(player->angle - PI);
				break;
			case SDL_SCANCODE_A:
				paceX = 2 * cos(player->angle - PI / 2);
				paceY = 2 * sin(player->angle - PI / 2);
				break;
			case SDL_SCANCODE_D:
				paceX = 2 * cos(player->angle + PI / 2);
				paceY = 2 * sin(player->angle + PI / 2);
				break;
			case SDL_SCANCODE_LEFT:
				player->angle -= PI / 90.0;
				break;
			case SDL_SCANCODE_RIGHT:
				player->angle += PI / 90.0;
				break;
			}
			player->x += paceX;
			player->y += paceY;
			break;
		}
	}
	return (0);
}
/*int no_collision(SDL_Player *player, int map[ROWS][COLS], int x, int y)
{
	int row, col;
	float x0, y0;

	x0 = player->x + 5 * x;
	y0 = player->y;
	row = y0 / BOXSIZE;
	col = x0 / BOXSIZE;
	if (map[row][col] != 0)
	{
		player->x = col * BOXSIZE - 5 *(abs(x) / x);
	}
	x0 = player->x;
	y0 = player->y + 5 * x;
	row = y0 / BOXSIZE;
	col = x0 / BOXSIZE;
	if (map[row][col] != 0)
	{
		player->y = row * BOXSIZE - 5 *(abs(y) / y);
		return (1);
	}
	return (0);
}*/