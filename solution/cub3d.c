/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 09:48:26 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/25 10:20:52 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_scene			scene;
	t_memory_info	*memory;

	memory = NULL;
	if (!parser(&scene, argc - 1, argv, memory))
		return (1);

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