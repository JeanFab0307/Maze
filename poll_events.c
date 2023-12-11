#include <SDL2/SDL.h>
#include <math.h>
#include "maze.h"

void search_collision_x(SDL_Player *player, int map[ROWS][COLS], float paceX);
void search_collision_y(SDL_Player *player, int map[ROWS][COLS], float paceY);

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
				paceX = 4 * cos(player->angle);
				paceY = 4 * sin(player->angle);
				break;
			case SDL_SCANCODE_S:
				paceX = 4 * cos(player->angle - PI);
				paceY = 4 * sin(player->angle - PI);
				break;
			case SDL_SCANCODE_A:
				paceX = 4 * cos(player->angle - PI / 2);
				paceY = 4 * sin(player->angle - PI / 2);
				break;
			case SDL_SCANCODE_D:
				paceX = 4 * cos(player->angle + PI / 2);
				paceY = 4 * sin(player->angle + PI / 2);
				break;
			case SDL_SCANCODE_LEFT:
				player->angle -= PI / 50.0;
				break;
			case SDL_SCANCODE_RIGHT:
				player->angle += PI / 50.0;
				break;
			}
			search_collision_x(player, map, paceX);
			search_collision_y(player, map, paceY);
			break;
		}
	}
	return (0);
}
void search_collision_x(SDL_Player *player, int map[ROWS][COLS], float paceX)
{
	int row, col, hit;
	float x1, tmp;

	tmp = player->x;
	x1 = player->x + paceX;
	row = player->y / BOXSIZE;
	col = x1 / BOXSIZE;
	hit = 0;
	if (map[row][col] != 0)
	{
		hit = 1;
		player->x = tmp - paceX;
	}

	if (hit == 0)
	{
		player->x = tmp + paceX;
	}
}

void search_collision_y(SDL_Player *player, int map[ROWS][COLS], float paceY)
{
	int row, col, hit;
	float y1, tmp;

	tmp = player->y;
	y1 = player->y + paceY;
	row = y1 / BOXSIZE;
	col = player->x / BOXSIZE;
	hit = 0;
	if (map[row][col] != 0)
	{
		hit = 1;
		player->y = tmp - paceY;
	}
	
	if (hit == 0)
	{
		player->y = tmp + paceY;
	}
}