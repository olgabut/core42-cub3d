/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:35:37 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/21 12:13:32 by obutolin         ###   ########.fr       */
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
	print_common_error(INVALID_FILE_EXTENTION);
	return (0);
}

int	check_argument(int arg_count)
{
	if (arg_count == 0)
		return (print_common_error(NO_ARGUMENT), 0);
	if (arg_count > 1)
		return (print_common_error(TOO_MANY_ARGUMENTS), 0);
	return (1);
}

int	check_struct_from_file(t_scene *scene)
{
	if (scene->north.texture == NULL)
		return (print_no_texture('N'), 0);
	if (scene->south.texture == NULL)
		return (print_no_texture('S'), 0);
	if (scene->west.texture == NULL)
		return (print_no_texture('W'), 0);
	if (scene->east.texture == NULL)
		return (print_no_texture('E'), 0);
	if (BONUS_MODE && scene->door.texture == NULL)
		return (print_no_texture('D'), 0);
	if (scene->ceiling.color[0] == -1)
	{
		print_file_content_warning(NO_COLOR, -1, "ceiling");
		scene->ceiling.color[0] = 255;
		scene->ceiling.color[1] = 255;
		scene->ceiling.color[2] = 255;
	}
	if (scene->floor.color[0] == -1)
	{
		print_file_content_warning(NO_COLOR, -1, "floor");
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
		print_file_content_error(NO_MAP, -1, "");
		return (0);
	}
	if (scene->map.player_orientation == ' ')
	{
		print_file_content_error(NO_STARTING_POSITION, -1, "");
		return (0);
	}
	scene->map.size_y = scene->map.last_line_in_file
		- scene->map.first_line_in_file + 1;
	return (1);
}
