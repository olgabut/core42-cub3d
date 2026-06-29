/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:59:36 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/29 11:47:12 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"
#include "read_file.h"
#include "analyzer.h"

	// t_texture	north;
	// t_texture	south;
	// t_texture	west;
	// t_texture	east;
	// t_color		floor;
	// t_color		ceiling;
	// t_map		map;
/*
The function is only needed to display the input data before rendering
*/
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
	printf("player position %c (%d, %d)\n", scene.map.player_orientation,
		scene.map.player_position_x, scene.map.player_position_y);
	printf("map size = (%zu, %zu)\n", scene.map.size_x, scene.map.size_y);
	print_map_list(scene.map.map_list_header);
	print_map_array(scene.map.map);
}

static void	init_scene(t_scene *scene)
{
	scene->data_status = OK;
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
	scene->map.first_line_in_file = -1;
	scene->map.last_line_in_file = -1;
	scene->map.map_list_header = NULL;
	scene->map.map = NULL;
	scene->map.size_x = 0;
	scene->map.size_y = 0;
	scene->map.player_orientation = ' ';
	scene->map.player_position_x = -1;
	scene->map.player_position_y = -1;
}

/*
	Return
		1 - ok
		0 - some error (stop program)
*/
int	parser(t_scene *scene, int arg_count, char **argv)
{
	if (!check_argument(arg_count) || !check_file_extantion(argv[1]))
		return (0);
	init_scene(scene);
	if (!read_file(scene, argv[1]))
		return (0);
	if (scene->data_status == WRONG
		|| !check_struct_from_file(scene) || !check_map_from_file(scene))
	{
		scene->data_status = WRONG;
		return (0);
	}
	if (!conver_map_list_to_arr(scene))
	{
		print_common_error(MEMORY_ERROR);
		return (0);
	}
	print_scene_struct(*scene);
	if (!check_map_array(scene))
		return (0);
	
	return (1);
}
