/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:21:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/09 11:43:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "analyzer.h"
#include "checker.h"

/*
	Return
		1 - it looks like a map line
		0 - it's not a map line
*/
int	does_line_contain_only_map_symbols(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		#ifdef BONUS
		if (line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' '
			&& line[i] != '0' && line[i] != '1' && line[i] != '2')
			return (0);
		#else
		if (line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' '
			&& line[i] != '0' && line[i] != '1')
			return (0);
		#endif
		i++;
	}
	return (1);
}

/*
	Return
	1- ok
	0 - error (duplicate player position)
*/
int	check_player_position(t_scene *scene, char *line, int line_num)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (scene->map.player_orientation != ' ')
			{
				print_file_content_error(MUPTIPLE_STARTING_POSITIONS,
					line_num, "");
				scene->data_status = WRONG;
				return (0);
			}
			scene->map.player_orientation = line[i];
			scene->map.player_position_x = i;
			scene->map.player_position_y = line_num
				- scene->map.first_line_in_file;
		}
		i++;
	}
	return (1);
}

void	analyse_map_line(t_scene *scene, char *line, int line_num)
{
	t_map_list	*map_node;
	size_t		len;

	(void)*scene;
	if (!does_line_contain_only_map_symbols(line))
	{
		print_file_content_error(UNSUPPORTED_CHARACTERS, line_num, "");
		scene->data_status = WRONG;
		return ;
	}
	scene->data_status = MAP_PROCESSING;
	len = ft_strlen(line);
	if (scene->map.first_line_in_file == -1)
		scene->map.first_line_in_file = line_num;
	scene->map.last_line_in_file = line_num;
	if (len > scene->map.size_x)
		scene->map.size_x = len;
	if (!check_player_position(scene, line, line_num))
		return ;
	create_map_list(&map_node, line);
	if (!map_node)
		return ;
	add_new_memory_link_for_control(&scene->memory, map_node);
	add_new_map_list(&(scene->map.map_list_header), map_node);
}
