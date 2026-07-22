/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 15:42:03 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/22 11:00:44 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"
#include <sys/time.h>

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	update_fire(t_graphics *g)
{
	long	now;

	now = get_time_ms();
	if (now - g->fire_last_time > 200)
	{
		g->fire_frame = (g->fire_frame + 1) % 5;
		g->fire_last_time = now;
		g->moved = 1;
	}
}

static void	draw_sprite_fire_horizontal(t_graphics *g, t_shape s,
		double sprite_dist, int y)
{
	int	x;
	int	color;
	int	tex_y;
	int	screen_x;
	int	column;

	tex_y = (y * s.img->height) / s.height;
	x = 0;
	while (x < s.width)
	{
		screen_x = s.x + x;
		if (screen_x >= 0 && screen_x < WINDOW_WIDTH)
		{
			color = get_pixel(s.img, (x * s.img->width) / s.width, tex_y);
			if ((color & 0x00FFFFFF) != 0)
			{
				column = screen_x;
				if (column >= 0 && column < WINDOW_WIDTH
					&& sprite_dist < g->wall_dist[column])
					put_pixel(&g->screen, screen_x, s.y + y, color);
			}
		}
		x++;
	}
}

void	draw_sprite_fire(t_graphics *g, t_shape s, double sprite_dist)
{
	int	y;
	int	screen_y;

	y = 0;
	while (y < s.height)
	{
		screen_y = s.y + y;
		if (screen_y < 0 || screen_y >= WINDOW_HEIGHT)
		{
			y++;
			continue ;
		}
		draw_sprite_fire_horizontal(g, s, sprite_dist, y);
		y++;
	}
}
