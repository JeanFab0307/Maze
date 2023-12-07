#include <SDL2/SDL.h>
#include <math.h>
#include "maze.h"

float calc_lenght(float x, float y);
float calc_impact(SDL_Player *player, int map[ROWS][COLS]);
float calc_impact_row(SDL_Player *player, int map[ROWS][COLS]);
float calc_impact_col(SDL_Player *player, int map[ROWS][COLS]);
void render_FOV(SDL_Instance instance, SDL_Player *player, float lenght);

void draw_map(SDL_Instance instance, int map[ROWS][COLS])
{
	SDL_Rect rect;
	int i, j, hit;

	rect.x = 1;
	rect.y = 1;
	rect.w = BOXSIZE - 2;
	rect.h = BOXSIZE - 2;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			if (map[i][j] == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0x06, 0xFF, 0x00, 0xFF);
			else
				SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(instance.renderer, &rect);
			rect.x += rect.w + 2;
		}
		rect.x = 1;
		rect.y += rect.h + 2;
	}
}

void draw_player(SDL_Instance instance, SDL_Player *player)
{
	SDL_FRect rect_p;

	rect_p.w = 10.0;
	rect_p.h = 10.0;
	rect_p.x = player->x - (rect_p.w / 2);
	rect_p.y = player->y - (rect_p.w / 2);
	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);	
	SDL_RenderFillRectF(instance.renderer, &rect_p);
}

void raycasting(SDL_Instance instance, SDL_Player *player, int map[ROWS][COLS])
{
	float lenght, tmp = player->angle;
	float i, lineHeight,start, end;
	int j, h = 720;

	j = 400;
	for (i = -player->FOV / 2; i <= player->FOV / 2; i += player->FOV / 600)
	{
		j++;
		player->angle = tmp + i;
		lenght = calc_impact(player, map);
		render_FOV(instance, player, lenght);
		lineHeight = h / ((lenght * cos(i)) / BOXSIZE);
		start = -lineHeight / 2 + h / 2;
		end = lineHeight / 2 + h / 2;
		if (start < 0)
			start = 0;
		if (end >= h)
			end = h - 1;
		SDL_SetRenderDrawColor(instance.renderer, 0x10, 0xFF, 0x10, 0xFF);
		SDL_RenderDrawLineF(instance.renderer, j, start, j, end);
		SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLineF(instance.renderer, j, 0, j, start);
		SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0x75, 0x12, 0xFF);
		SDL_RenderDrawLineF(instance.renderer, j, end, j, h);
	}
	player->angle = tmp;
}
void render_FOV(SDL_Instance instance, SDL_Player *player, float lenght)
{
	float x0, y0, x1, y1;

	x0 = player->x;
	y0 = player->y;
	x1 = lenght * cos(player->angle) + x0;
	y1 = lenght * sin(player->angle) + y0;
	SDL_SetRenderDrawColor(instance.renderer, 0x8F, 0x8F, 0x8F, 0xFF);
	SDL_RenderDrawLineF(instance.renderer, x0, y0, x1, y1);
}

float calc_impact(SDL_Player *player, int map[ROWS][COLS])
{
	float real_lenght, lenght0, lenght1;

	lenght0 = calc_impact_row(player, map);
	lenght1 = calc_impact_col(player, map);
	if (lenght0 <= lenght1)
	{
		real_lenght = lenght0; 
	}
	else
	{
		real_lenght = lenght1;
	}
	return (real_lenght);
}

float calc_lenght(float x, float y)
{
	x *= x;
	y *= y;
	return (sqrt(x + y));
}

float calc_impact_row(SDL_Player *player, int map[ROWS][COLS])
{
	int i, hit, mapY, row, col;
	float x0, y0, x1, y1;


	x0 = player->x, y0 = player->y;
	mapY = player->y / BOXSIZE;
	hit = 0;
	i = 0;
	while (hit == 0)
	{
		if (sin(player->angle) >= 0)
		{
			y1 = (mapY + 1 + i) * BOXSIZE;
			x1 = abs(y1 - y0) / tan(player->angle) + x0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;
			if ((row < 0 || row >= ROWS) || (col < 0 || col >= COLS))
				hit = 1;
			else if (map[row][col] != 0)
				hit = 1;
		}
		else
		{
			y1 = (mapY - i) * BOXSIZE;
			x1 = -abs(y1 - y0) / tan(player->angle) + x0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;
			if ((row < 0 || row >= ROWS) || (col < 0 || col >= COLS))
			{
				hit = 1;
			}
			else if (map[row - 1][col] != 0)
			{
				hit = 1;
			}
		}
		i++;
	}
	return (calc_lenght((x0 - x1), (y0 - y1)));
}
float calc_impact_col(SDL_Player *player, int map[ROWS][COLS])
{
	int i, hit, mapX, row, col;
	float x0, y0, x1, y1;

	x0 = player->x, y0 = player->y;
	mapX = player->x / BOXSIZE;
	hit = 0;
	i = 0;
	while (hit == 0)
	{
		if (cos(player->angle) >= 0)
		{
			x1 = (mapX + 1 + i) * BOXSIZE;
			y1 = (x1 - x0) * tan(player->angle) + y0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;
			if ((row < 0 || row >= ROWS) || (col < 0 || col >= COLS))
				hit = 1;
			else if (map[row][col] != 0)
				hit = 1;
		}
		else
		{
			x1 = (mapX - i) * BOXSIZE;
			y1 = (x1 - x0) * tan(player->angle) + y0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;
			if ((row < 0 || row >= ROWS) || (col < 0 || col >= COLS))
				hit = 1;
			else if (map[row][col - 1] != 0)
				hit = 1;
		}
		i++;
	}
	return (calc_lenght((x0 - x1), (y0 - y1)));
}