#include <SDL2/SDL.h>
#include "../inc/maze.h"

void draw_map(SDL_Instance instance, SDL_Player *player, map_t map)
{
	SDL_Rect rect;
	int i, j, hit;

	rect.x = 1;
	rect.y = 1;
	rect.w = MINIMAPW / map.cols;
	rect.h = MINIMAPH / map.rows;
	for (i = 0; i < map.rows; i++)
	{
		for (j = 0; j < map.cols; j++)
		{
			if (map.layout[i][j] == 0)
				set_color(&instance, "green");
			else if (map.layout[i][j] == 5)
				set_color(&instance, "yellow");
			else
				set_color(&instance, "white");
			SDL_RenderFillRect(instance.renderer, &rect);
			rect.x += rect.w;
		}
		rect.x = 1;
		rect.y += rect.h;
	}
	draw_player(instance, player, MINIMAPW / map.cols, MINIMAPH / map.rows);
}

void draw_player(SDL_Instance instance, SDL_Player *player, int width_ratio, int height_ratio)
{
	SDL_FRect rect_p;
	float x1, y1, x0, y0;

	x0 = player->x / BOXSIZE * width_ratio;
	y0 = player->y / BOXSIZE * height_ratio;
	x1 = 20 * cos(player->angle) + x0;
	y1 = 20 * sin(player->angle) + y0;
	rect_p.w = 8;
	rect_p.h = 8;
	rect_p.x = x0 - (rect_p.w / 2);
	rect_p.y = y0 - (rect_p.w / 2);
	set_color(&instance, "red");	
	SDL_RenderFillRectF(instance.renderer, &rect_p);
	SDL_RenderDrawLineF(instance.renderer, x0, y0, x1, y1);
}

void raycasting(SDL_Instance instance, SDL_Player *player, map_t map)
{
	float lenght, tmp = player->angle;
	float i, lineHeight;
	int j;

	j = 0;
	for (i = -player->FOV / 2; i <= player->FOV / 2; i += player->FOV / SCREENWIDTH)
	{
		j += 1;
		player->angle = tmp + i;
		lenght = calc_impact(instance, player, map);
		lineHeight = SCREENHEIGHT / ((lenght * cos(i)) / BOXSIZE);
		draw_line(instance, lineHeight, j);
	}
	player->angle = tmp;
}

void draw_line(SDL_Instance instance, double lineHeight, int lineX)
{
	float start, end;

	start = -lineHeight / 2 + SCREENHEIGHT / 2;
	end = lineHeight / 2 + SCREENHEIGHT / 2;
	if (start < 0)
		start = 0;
	if (end >= SCREENHEIGHT)
		end = SCREENHEIGHT - 1;
	SDL_RenderDrawLineF(instance.renderer, lineX, start, lineX, end);
	set_color(&instance, "blue");
	SDL_RenderDrawLineF(instance.renderer, lineX, 0, lineX, start);
	set_color(&instance, "brown");
	SDL_RenderDrawLineF(instance.renderer, lineX, end, lineX, SCREENHEIGHT);
}
