/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall_at_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/21 15:08:13 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static int	check_cell_at(t_graphics *g, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)(x / 64);
	map_y = (int)(y / 64);
	if (map_x < 0 || map_y < 0
		|| map_x >= (int)g->scene->map.size_x
		|| map_y >= (int)g->scene->map.size_y)
		return (1);
	cell = g->scene->map.map[map_y][map_x];
	if (cell == '1'
		|| (cell == '2' && g->door_state[map_y][map_x] == 0))
		return (1);
	return (0);
}

int	is_wall_at(t_graphics *g, double x, double y, double margin)
{
	return (check_cell_at(g, x + margin, y + margin)
		|| check_cell_at(g, x - margin, y - margin)
		|| check_cell_at(g, x + margin, y - margin)
		|| check_cell_at(g, x - margin, y + margin));
}

/* Updates player position and rotation based on key presses */
void	update_player_bonus(t_graphics *graphics)
{
	double	new_x;
	double	new_y;
	double	margin;

	margin = 8.0;
	new_x = graphics->player.x + move_player_x(graphics);
	new_y = graphics->player.y + move_player_y(graphics);
	if (!is_wall_at(graphics, new_x, graphics->player.y, margin))
		graphics->player.x = new_x;
	if (!is_wall_at(graphics, graphics->player.x, new_y, margin))
		graphics->player.y = new_y;
	if (graphics->keys_pressed[KEY_LEFT])
		graphics->player.angle -= graphics->rotate_speed;
	if (graphics->keys_pressed[KEY_RIGHT])
		graphics->player.angle += graphics->rotate_speed;
}
