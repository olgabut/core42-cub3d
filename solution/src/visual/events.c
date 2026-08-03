/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/08/03 16:25:20 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

int	handle_key_press(int keycode, t_graphics *graphics)
{
	if (keycode == KEY_ESC)
	{
		free_graphics(graphics);
		free_memory_links(&graphics->scene->memory);
		exit(0);
	}
	if (BONUS_MODE && keycode == KEY_F)
		toggle_door(graphics);
	if (keycode >= 0 && keycode < 70000)
		graphics->keys_pressed[keycode] = 1;
	return (0);
}

int	handle_key_release(int keycode, t_graphics *graphics)
{
	if (keycode >= 0 && keycode < 70000)
		graphics->keys_pressed[keycode] = 0;
	return (0);
}

int	handle_close(t_graphics *graphics)
{
	free_graphics(graphics);
	free_memory_links(&graphics->scene->memory);
	exit(0);
}
