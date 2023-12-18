#include <SDL2/SDL.h>
#include "../inc/maze.h"


/**
 * main - entry point in the program
 *
 * Return: 0 on success else 1
 */
int main(void)
{
	SDL_Instance instance;
	SDL_Player player;
	SDL_bool minimap = SDL_TRUE;
	map_t map = init_map("maps/map");

	if (init_instance(&instance) !=0)
		return (1);
	
	init_player(&player, 6.0, 5.0, -PI / 2, PI / 3); 
	/*the coordonates given are those in the maps*/

	while ("gg")
	{
		set_color(&instance, "");
		SDL_RenderClear(instance.renderer);
		if (poll_events(&player, map, &minimap) == 1)
			break;
		raycasting(instance, &player, map);
		if (minimap != 0)
		{
			draw_map(instance, &player, map);
		}
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return(0);
}
