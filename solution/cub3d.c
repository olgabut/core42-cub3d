/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 09:48:26 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/03 21:50:22 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_scene			scene;

	scene.memory = NULL;
	if (!parser(&scene, argc - 1, argv))
		return (1);
	free_memory_links(&scene.memory);

	// void	*mlx;
	// void	*win;

	// printf("prog = %s\n", argv[0]);
	// if (argc > 1)
	// 	printf("argv[1] = %s\n", argv[0]);

	// mlx = mlx_init();
	// if (!mlx)
	// 	return (1);

	// win = mlx_new_window(mlx, 800, 600, "MLX Test");
	// if (!win)
	// 	return (1);

	// mlx_loop(mlx);
	return (0);
}