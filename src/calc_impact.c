#include "../inc/maze.h"

float calc_impact(SDL_Instance inst,SDL_Player *player, map_t map)
{
	float real_lenght, lenght0, lenght1;

	lenght0 = calc_impact_row(player, map);
	lenght1 = calc_impact_col(player, map);
	if (lenght0 < lenght1)
	{
		real_lenght = lenght0;
		set_color(&inst, "green");
	}
	else
	{
		real_lenght = lenght1;
		set_color(&inst, "dark green");
	}
	return (real_lenght);
}

float calc_lenght(float x, float y)
{
	x *= x;
	y *= y;
	return (sqrt(x + y));
}

float calc_impact_row(SDL_Player *player, map_t map)
{
	int i, hit, mapY, row, col;
	double x0, y0, x1, y1;


	x0 = player->x, y0 = player->y;
	mapY = player->y / BOXSIZE;
	hit = 0;
	i = 0;
	while (hit == 0)
	{
		if (sin(player->angle) >= 0)
		{
			y1 = (mapY + 1 + i) * BOXSIZE;
			x1 = abs(y1 - y0) / tan(player->angle) + x0 ;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;
			
			if ((row < 0 || row >= map.rows) || (col < 0 || col >= map.cols))
				hit = 1;
			else if (map.layout[row][col] != 0)
				hit = 1;
		}
		else
		{
			y1 = (mapY - i) * BOXSIZE ;
			x1 = -abs(y1 - y0) / tan(player->angle) + x0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;
			if ((row < 0 || row >= map.rows) || (col < 0 || col >= map.cols))
				hit = 1;
			else if (map.layout[row - 1][col] != 0)
				hit = 1;
		}
		i++;
	}
	return (calc_lenght((x0 - x1), (y0 - y1)));
}
float calc_impact_col(SDL_Player *player,map_t map)
{
	int i, hit, mapX, row, col;
	double x0, y0, x1, y1;

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
			if ((row < 0 || row >= map.rows) || (col < 0 || col >= map.cols))
				hit = 1;
			else if (map.layout[row][col] != 0)
				hit = 1;
		}
		else
		{
			x1 = (mapX - i) * BOXSIZE;
			y1 = (x1 - x0) * tan(player->angle) + y0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;
			if ((row < 0 || row >= map.rows) || (col < 0 || col >= map.cols))
				hit = 1;
			else if (map.layout[row][col - 1] != 0)
				hit = 1;
		}
		i++;
	}
	return (calc_lenght((x0 - x1), (y0 - y1)));
}
