/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:59:36 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/29 11:55:55 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"
#include "read_file.h"

	// t_texture	north; //NO
	// t_texture	south;
	// t_texture	west;
	// t_texture	east;
	// t_color		floor;
	// t_color		ceiling;
	// t_map		map;
void	print_scene_struct(t_scene scene)
{
	printf("NO = '%s'\n", scene.north.texture);
	printf("SO = '%s'\n", scene.south.texture);
	printf("WE = '%s'\n", scene.west.texture);
	printf("EA = '%s'\n", scene.east.texture);
	printf("ceilind RGB(%d, %d, %d)\n",
		scene.ceiling.color[0], scene.ceiling.color[1], scene.ceiling.color[2]);
	printf("floor RGB(%d, %d, %d)\n",
		scene.floor.color[0], scene.floor.color[1], scene.floor.color[2]);
}

void	init_scene(t_scene *scene)
{
	scene->north.texture = NULL;
	scene->south.texture = NULL;
	scene->west.texture = NULL;
	scene->east.texture = NULL;
	scene->ceiling.color[0] = -1;
	scene->ceiling.color[1] = -1;
	scene->ceiling.color[2] = -1;
	scene->floor.color[0] = -1;
	scene->floor.color[1] = -1;
	scene->floor.color[2] = -1;
}

/*
	Return
		1 - ok
		0 - some error (stop program)
*/
int	parser(t_scene *scene, int arg_count, char **argv, t_memory_info **memory)
{
	if (!check_argument(arg_count) || !check_file_extantion(argv[1]))
		return (0);
	init_scene(scene);
	if (!read_file(scene, argv[1], memory))
		return (0);
	print_scene_struct(*scene);
	return (1);
}
