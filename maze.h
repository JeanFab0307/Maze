#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>

#define ROWS 10
#define COLS 10
#define BOXSIZE 32 /*how big a case in the map is in pixel*/
#define PI 3.14159265

/**
 * struct SDL_Instance - instance of a SDL window and renderer
 * @window: The window object we'l be rendering to
 * @renderer: the renderer object
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
 * struct SDL_Player - instance of a player in the maze
 * @x: the x coordonate on the map
 * @y: the y coordonate on the map
 * @dirX: the x coor direction the player is facing
 * @dirY: the y coor direction the player is facing
 */

typedef struct SDL_Player
{
	float x;
	float y;
	float angle;
	float FOV;
} SDL_Player;

typedef struct color
{
	char *name;
	int RGB[4];
} color_t;

int poll_events(SDL_Player *player, int map[ROWS][COLS]);
void draw_map(SDL_Instance instance, int map[ROWS][COLS]);
void draw_player(SDL_Instance instance, SDL_Player *player);
void raycasting(SDL_Instance instance, SDL_Player *player, int map[ROWS][COLS]);
void set_color(SDL_Instance *instance, char *color);
#endif
