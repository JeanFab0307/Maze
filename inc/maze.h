#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MINIMAPW 200
#define MINIMAPH 200
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

typedef struct map_t
{
	int rows;
	int cols;
	int **layout;
} map_t;

int poll_events(SDL_Player *player, map_t map, SDL_bool *minimap);

void draw_map(SDL_Instance instance, SDL_Player *player, map_t map);

void draw_player(SDL_Instance instance, SDL_Player *player, int width_ratio, int height_ratio);
void raycasting(SDL_Instance instance, SDL_Player *player, map_t map);
void set_color(SDL_Instance *instance, char *color);

int init_instance(SDL_Instance *instance);
void init_player(SDL_Player *player, float X, float Y, float angle, float FOV);
map_t init_map(char *filename);

void close_file(FILE *fp);
FILE *open_file(char *filename);
map_t read_file(FILE *fp);
int count_rows(FILE *fp);

float calc_lenght(float x, float y);
float calc_impact(SDL_Instance inst, SDL_Player *player, map_t map);
float calc_impact_row(SDL_Player *player, map_t map);
float calc_impact_col(SDL_Player *player, map_t map);
#endif
