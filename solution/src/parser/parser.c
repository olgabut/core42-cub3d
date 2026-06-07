/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:59:36 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/07 18:04:22 by obutolin         ###   ########.fr       */
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
void	print_scene_struct(t_scene scene)
{
	size_t i, j;

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
	printf("Map array:");
	for(i = 0; i < scene.map.size_y; i++)
	{
		printf("'");
		for (j = 0; j < scene.map.size_x; j++)
		{
			printf("%c", scene.map.map[i][j]);
		}
		printf("'\n");
	}
}

void	init_scene(t_scene *scene)
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

int conver_map_list_to_arr(t_scene *scene)
{
	char **map;
	t_map_list *list_line;
	size_t i;
	size_t j;
	size_t list_line_len;

	map = malloc((scene->map.size_y + 1) * sizeof(char *));
	if (!map)
		return (0);
	add_new_memory_link_for_control(&scene->memory, map);
	i = 0;
	list_line = scene->map.map_list_header;
	while(i < scene->map.size_y)
	{
		map[i] = malloc((scene->map.size_x + 1) * sizeof(char));
		if (!map[i])
			return (0);
		add_new_memory_link_for_control(&scene->memory, map[i]);
		j = 0;
		list_line_len = ft_strlen(list_line->line);
		while(j < scene->map.size_x)
		{
			if (list_line_len > j)
				map[i][j] = list_line->line[j];
			else
				map[i][j] = ' ';
			j++;
		}
	    map[i][scene->map.size_x] = '\0';
	    list_line = list_line->next;
	    i++;
	}
	map[scene->map.size_y] = NULL;
	scene->map.map = map;
	return (1);
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
	if (!check_data_from_file(scene) || !check_map_from_file(scene))
		return (0);
	conver_map_list_to_arr(scene);
	print_scene_struct(*scene);
	return (1);
}
