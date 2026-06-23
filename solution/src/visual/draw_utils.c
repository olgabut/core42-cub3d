#include "renderer.h"

void	put_pixel(t_image *image, int x, int y, int color)
{
	unsigned int	*pixel;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	pixel = (unsigned int *)(image->data + (y * image->size_line + x * (image->bpp / 8)));
	*pixel = color;
}

void	draw_floor_ceiling(t_graphics *g)
{
	int	y;
	int	x;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = (g->scene->ceiling.color[0] << 16) | (g->scene->ceiling.color[1] << 8) | g->scene->ceiling.color[2];
	floor_color = (g->scene->floor.color[0] << 16) | (g->scene->floor.color[1] << 8) | g->scene->floor.color[2];
	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(&g->screen, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	y = WINDOW_HEIGHT / 2;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel(&g->screen, x, y, floor_color);
			x++;
		}
		y++;
	}
}
