/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:08:23 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/22 11:32:35 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int	init_fire_texture(t_graphics *graphics)
{
	if (!load_texture(graphics, &graphics->fire_frames[0],
			"./scenes/texture/fire/fire01.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[1],
			"./scenes/texture/fire/fire02.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[2],
			"./scenes/texture/fire/fire03.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[3],
			"./scenes/texture/fire/fire04.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[4],
			"./scenes/texture/fire/fire05.xpm"))
		return (0);
	return (1);
}

void	free_fire_img(t_graphics *graphics)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (graphics->fire_frames[i].ptr)
			mlx_destroy_image(graphics->mlx, graphics->fire_frames[i].ptr);
		i++;
	}
}

int	fire_shape_preparation(t_graphics *g, t_shape *shape, int dx, int dy)
{
	int		size;
	double	dist;
	double	screen_x;
	double	side;
	double	forward;

	dist = sqrt(dx * dx + dy * dy) / 64.0;
	forward = dx * cos(g->player.angle) + dy * sin(g->player.angle);
	side = -dx * sin(g->player.angle) + dy * cos(g->player.angle);
	if (forward <= 0)
		return (0);
	screen_x = WINDOW_WIDTH / 2 + (side / forward)
		* (WINDOW_WIDTH / (2
				* tan(atan2(0.5, (double)WINDOW_HEIGHT / WINDOW_WIDTH))));
	size = (int)(WINDOW_HEIGHT / (dist * 0.8));
	shape->x = (int)screen_x - size / 2;
	shape->y = (WINDOW_HEIGHT - size) / 2;
	shape->width = size;
	shape->height = size;
	shape->img = &g->fire_frames[g->fire_frame];
	return (1);
}

void	draw_fire(t_graphics *g)
{
	int		x;
	int		y;
	double	dx;
	double	dy;
	t_shape	shape;

	y = -1;
	while (++y < (int)g->scene->map.size_y)
	{
		x = -1;
		while (++x < (int)g->scene->map.size_x)
		{
			if (g->scene->map.map[y][x] != '3')
				continue ;
			dx = (x * 64 + 32) - g->player.x;
			dy = (y * 64 + 32) - g->player.y;
			if (!fire_shape_preparation(g, &shape, dx, dy))
				continue ;
			draw_sprite_fire(g, shape, sqrt(dx * dx + dy * dy) / 64.0);
		}
	}
}
