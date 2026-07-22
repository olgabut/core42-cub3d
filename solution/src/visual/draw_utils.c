/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/21 14:18:39 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	put_pixel(t_image *image, int x, int y, int color)
{
	unsigned int	*pixel;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	pixel = (unsigned int *)(image->data
			+ (y * image->size_line + x * (image->bpp / 8)));
	*pixel = color;
}

static void	draw_floor(t_graphics *g)
{
	int	y;
	int	x;
	int	floor_color;

	floor_color = (g->scene->floor.color[0] << 16)
		| (g->scene->floor.color[1] << 8)
		| g->scene->floor.color[2];
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

static void	draw_ceiling(t_graphics *g)
{
	int	y;
	int	x;
	int	ceiling_color;

	ceiling_color = (g->scene->ceiling.color[0] << 16)
		| (g->scene->ceiling.color[1] << 8)
		| g->scene->ceiling.color[2];
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
}

void	draw_floor_ceiling(t_graphics *g)
{
	draw_ceiling(g);
	draw_floor(g);
}
