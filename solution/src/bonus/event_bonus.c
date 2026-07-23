/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/23 10:15:19 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int	handle_mouse(int x, int y, t_graphics *graphics)
{
	static int	ignore;
	int			dx;
	int			center;

	(void)y;
	if (ignore)
	{
		ignore = 0;
		return (0);
	}
	center = WINDOW_WIDTH / 2;
	if (x == center)
		return (0);
	dx = x - center;
	graphics->player.angle += (double)dx * 0.003;
	mlx_mouse_move(graphics->mlx,
		graphics->window, center, WINDOW_HEIGHT / 2); // Linux
	// mlx_mouse_move(graphics->window, center, WINDOW_HEIGHT / 2); // MacOS
	return (0);
}

void	toggle_door(t_graphics *g)
{
	int		map_x;
	int		map_y;
	double	check_x;
	double	check_y;

	check_x = g->player.x + cos(g->player.angle) * 64;
	check_y = g->player.y + sin(g->player.angle) * 64;
	map_x = (int)(check_x / 64);
	map_y = (int)(check_y / 64);
	if (map_x < 0 || map_y < 0
		|| map_x >= (int)g->scene->map.size_x
		|| map_y >= (int)g->scene->map.size_y)
		return ;
	if (g->scene->map.map[map_y][map_x] == '2')
		g->door_state[map_y][map_x] ^= 1;
}
