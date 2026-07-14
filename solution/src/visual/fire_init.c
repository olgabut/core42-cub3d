#include "renderer.h"

int	init_fire_texture(t_graphics *graphics)
{
	if (!load_texture(graphics, &graphics->fire, "./scenes/texture/fire/fire01.xpm"))
		return (0);
	return (1);
}

void	free_fire_img(t_graphics *graphics)
{
	// int i;

	if (graphics->fire.ptr)
		mlx_destroy_image(graphics->mlx, graphics->fire.ptr);
	// i = 0;
	// while (i < 5)
	// {
		
	// 	i++;
	// }
}