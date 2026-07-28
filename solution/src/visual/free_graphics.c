/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/27 14:39:35 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

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
	if (BONUS_MODE)
	{
		if (graphics->door.ptr)
			mlx_destroy_image(graphics->mlx, graphics->door.ptr);
		free_fire_img(graphics);
	}
	if (graphics->window)
		mlx_destroy_window(graphics->mlx, graphics->window);
	if (graphics->mlx)
	{
		mlx_destroy_display(graphics->mlx); // Linux
		free(graphics->mlx);
	}
}
