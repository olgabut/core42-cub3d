/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:35:37 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/07 17:41:19 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

int	check_file_extantion(char *fname)
{
	int	len;

	len = ft_strlen(fname);
	if (fname[len - 4] == '.'
		&& fname[len - 3] == 'c'
		&& fname[len - 2] == 'u'
		&& fname[len - 1] == 'b')
		return (1);
	return (print_invalid_file_extension(), 0);
}

int	check_argument(int arg_count)
{
	if (arg_count == 0)
		return (print_no_argument(), 0);
	if (arg_count > 1)
		return (print_too_many_arguments(), 0);
	return (1);
}

int	check_data_from_file(t_scene *scene)
{
	if (scene->north.texture == NULL)
		return (print_no_texture('N'), 0);
	if (scene->south.texture == NULL)
		return (print_no_texture('S'), 0);
	if (scene->west.texture == NULL)
		return (print_no_texture('W'), 0);
	if (scene->east.texture == NULL)
		return (print_no_texture('E'), 0);
	if (scene->ceiling.color[0] == -1)
	{
		printf("Warning\nThe file doesn't specify a color for the ceiling. ");
		printf("The ceiling will be white (default value).");
		scene->ceiling.color[0] = 255;
		scene->ceiling.color[1] = 255;
		scene->ceiling.color[2] = 255;
	}
	if (scene->floor.color[0] == -1)
	{
		printf("Warning\nThe file doesn't specify a color for the floor. ");
		printf("The floor will be black (default value).");
		scene->ceiling.color[0] = 0;
		scene->ceiling.color[1] = 0;
		scene->ceiling.color[2] = 0;
	}
	return (1);
}

int	check_map_from_file(t_scene *scene)
{
	if (scene->map.map_list_header == NULL
		|| scene->map.first_line_in_file == -1
		|| scene->map.last_line_in_file == scene->map.first_line_in_file)
	{
		printf("Error\nThere is not a map.\n");
		return (0);
	}
	if (scene->map.player_orientation == ' ')
	{
		printf("Error\nThe player's starting position (N, S, W, E) ");
		printf("is not indicated on the map.\n");
		return (0);
	}
	scene->map.size_y =
		scene->map.last_line_in_file - scene->map.first_line_in_file + 1;
	return (1);
}
