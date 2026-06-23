#include "renderer.h"

int	load_texture(t_graphics *graphics, t_image *img, const char *path)
{
	if (!path)
	{
		ft_putstr_fd("Error: texture path is NULL\n", 2);
		return (0);
	}
	img->ptr = mlx_xpm_file_to_image(graphics->mlx, (char *)path, &img->width, &img->height);
	if (!img->ptr)
	{
		fprintf(stderr, "Error: Failed to load texture %s\n", path);
		return (0);
	}
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line, &img->endian);
	return (1);
}

int	init_graphics(t_graphics *graphics, t_scene *scene)
{
	int	i;

	ft_bzero(graphics, sizeof(t_graphics));
	ft_bzero(graphics->door_state, sizeof(graphics->door_state));
	graphics->mlx = mlx_init();
	if (!graphics->mlx)
		return (0);
	graphics->window = mlx_new_window(graphics->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3D");
	if (!graphics->window)
		return (0);
	graphics->screen.ptr = mlx_new_image(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!graphics->screen.ptr)
		return (0);
	graphics->screen.data = mlx_get_data_addr(graphics->screen.ptr, &graphics->screen.bpp, &graphics->screen.size_line, &graphics->screen.endian);
	graphics->screen.width = WINDOW_WIDTH;
	graphics->screen.height = WINDOW_HEIGHT;
	graphics->scene = scene;
	graphics->player.x = scene->map.player_position_x * 64 + 32;
	graphics->player.y = scene->map.player_position_y * 64 + 32;
	if (scene->map.player_orientation == 'N')
		graphics->player.angle = 3 * PI / 2;
	else if (scene->map.player_orientation == 'S')
		graphics->player.angle = PI / 2;
	else if (scene->map.player_orientation == 'E')
		graphics->player.angle = 0;
	else if (scene->map.player_orientation == 'W')
		graphics->player.angle = PI;
	graphics->move_speed = 7.0;
	graphics->rotate_speed = 0.1;
	i = 0;
	while (i < 256)
	{
		graphics->keys_pressed[i] = 0;
		i++;
	}
	if (!load_texture(graphics, &graphics->north, scene->north.texture))
		return (0);
	if (!load_texture(graphics, &graphics->south, scene->south.texture))
		return (0);
	if (!load_texture(graphics, &graphics->west, scene->west.texture))
		return (0);
	if (!load_texture(graphics, &graphics->east, scene->east.texture))
		return (0);
	return (1);
}

void	free_graphics(t_graphics *graphics)
{
	if (graphics->screen.ptr)
		mlx_destroy_image(graphics->mlx, graphics->screen.ptr);
	if (graphics->north.ptr)
		mlx_destroy_image(graphics->mlx, graphics->north.ptr);
	if (graphics->south.ptr)
		mlx_destroy_image(graphics->mlx, graphics->south.ptr);
	if (graphics->west.ptr)
		mlx_destroy_image(graphics->mlx, graphics->west.ptr);
	if (graphics->east.ptr)
		mlx_destroy_image(graphics->mlx, graphics->east.ptr);
	if (graphics->window)
		mlx_destroy_window(graphics->mlx, graphics->window);
}

