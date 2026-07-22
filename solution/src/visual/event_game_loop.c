/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_game_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/21 14:41:45 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

double	move_player_x(t_graphics *graphics)
{
	if (graphics->keys_pressed[KEY_W])
		return (cos(graphics->player.angle) * graphics->move_speed);
	if (graphics->keys_pressed[KEY_S])
		return (-1 * cos(graphics->player.angle) * graphics->move_speed);
	if (graphics->keys_pressed[KEY_A])
		return (-1 * cos(graphics->player.angle + PI / 2)
			* graphics->move_speed);
	if (graphics->keys_pressed[KEY_D])
		return (cos(graphics->player.angle + PI / 2)
			* graphics->move_speed);
	return (0);
}

double	move_player_y(t_graphics *graphics)
{
	if (graphics->keys_pressed[KEY_W])
		return (sin(graphics->player.angle) * graphics->move_speed);
	if (graphics->keys_pressed[KEY_S])
		return (-1 * sin(graphics->player.angle) * graphics->move_speed);
	if (graphics->keys_pressed[KEY_A])
		return (-1 * sin(graphics->player.angle + PI / 2)
			* graphics->move_speed);
	if (graphics->keys_pressed[KEY_D])
		return (sin(graphics->player.angle + PI / 2)
			* graphics->move_speed);
	return (0);
}

/* Updates player position and rotation based on key presses */
static void	update_player(t_graphics *graphics)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = graphics->player.x + move_player_x(graphics);
	new_y = graphics->player.y + move_player_y(graphics);
	map_x = (int)(new_x / 64);
	map_y = (int)(new_y / 64);
	if (map_x >= 0
		&& map_x < (int)graphics->scene->map.size_x
		&& map_y >= 0
		&& map_y < (int)graphics->scene->map.size_y
		&& graphics->scene->map.map[map_y][map_x] != '1')
	{
		graphics->player.x = new_x;
		graphics->player.y = new_y;
	}
	if (graphics->keys_pressed[KEY_LEFT])
		graphics->player.angle -= graphics->rotate_speed;
	if (graphics->keys_pressed[KEY_RIGHT])
		graphics->player.angle += graphics->rotate_speed;
}

/* Main game loop */
int	game_loop(t_graphics *graphics)
{
	if (BONUS_MODE)
	{
		update_fire(graphics);
		update_player_bonus(graphics);
	}
	else
		update_player(graphics);
	render_frame(graphics);
	return (0);
}
