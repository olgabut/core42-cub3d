/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 09:48:26 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/23 15:07:28 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "renderer.h"

static void	visual_init_bonus(t_graphics *graphics)
{
	mlx_hook(graphics->window, 6, 1L << 6, handle_mouse, graphics);
	// mlx_mouse_hide(); // MacOS
	mlx_mouse_hide(graphics->mlx, graphics->window); // Linux
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_graphics	graphics;

	scene.memory = NULL;
	if (!parser(&scene, argc - 1, argv))
	{
		free_memory_links(&scene.memory);
		return (1);
	}
	if (!init_graphics(&graphics, &scene))
	{
		free_graphics(&graphics);
		free_memory_links(&scene.memory);
		return (1);
	}
	mlx_hook(graphics.window, 2, 1L << 0, handle_key_press, &graphics);
	mlx_hook(graphics.window, 3, 1L << 1, handle_key_release, &graphics);
	mlx_hook(graphics.window, 17, 1L << 17, handle_close, &graphics);
	if (BONUS_MODE)
		visual_init_bonus(&graphics);
	mlx_loop_hook(graphics.mlx, game_loop, &graphics);
	mlx_loop(graphics.mlx);
	free_graphics(&graphics);
	free_memory_links(&scene.memory);
	return (0);
}
