#include "renderer.h"

int	load_texture(t_graphics *graphics, t_image *img, const char *path)
{
	if (!path)
	{
		ft_putstr_fd("Error\ntexture path is NULL.\n", 2);
		return (0);
	}
	img->ptr = mlx_xpm_file_to_image(graphics->mlx, (char *)path,
			&img->width, &img->height);
	if (!img->ptr)
	{
		fprintf(stderr, "Error\nFailed to load texture %s.\n", path);
		return (0);
	}
	img->data = mlx_get_data_addr(img->ptr, &img->bpp, &img->size_line,
			&img->endian);
	return (1);
}

static int	graphics_preparation(t_graphics *gr)
{
	gr->mlx = mlx_init();
	if (!gr->mlx)
	{
		printf("Error\nmlx initialization failed.\n");
		return (0);
	}
	gr->window = mlx_new_window(gr->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!gr->window)
	{
		printf("Error\nWindow initialization failed.\n");
		return (0);
	}
	gr->screen.ptr = mlx_new_image(gr->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!gr->screen.ptr)
	{
		printf("Error\nImage initialization failed.\n");
		return (0);
	}
	gr->screen.data = mlx_get_data_addr(gr->screen.ptr, &gr->screen.bpp,
			&gr->screen.size_line, &gr->screen.endian);
	gr->screen.width = WINDOW_WIDTH;
	gr->screen.height = WINDOW_HEIGHT;
	return (1);
}

static void	set_player_angle(t_graphics *graphics,
	char player_orientation)
{
	if (player_orientation == 'N')
		graphics->player.angle = 3 * PI / 2;
	else if (player_orientation == 'S')
		graphics->player.angle = PI / 2;
	else if (player_orientation == 'E')
		graphics->player.angle = 0;
	else if (player_orientation == 'W')
		graphics->player.angle = PI;
}

int	init_graphics(t_graphics *graphics, t_scene *scene)
{
	int	i;

	ft_bzero(graphics, sizeof(t_graphics));
	ft_bzero(graphics->door_state, sizeof(graphics->door_state));
	if (!graphics_preparation(graphics))
		return (0);
	graphics->scene = scene;
	graphics->player.x = scene->map.player_position_x * 64 + 32;
	graphics->player.y = scene->map.player_position_y * 64 + 32;
	set_player_angle(graphics, scene->map.player_orientation);
	graphics->move_speed = 7.0;
	graphics->rotate_speed = 0.1;
	i = 0;
	while (i < 70000)
		graphics->keys_pressed[i++] = 0;
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
	if (graphics->mlx)
	{
		//mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
	}
}
