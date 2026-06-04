/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:21:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/04 14:57:18 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Return
		line_len - it looks like a map line (return line_len)
		0 - it's not a map line
*/
int	does_line_contain_only_map_symbols(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' '
			&& line[i] != '0' && line[i] != '1')
			return (0);
		i++;
	}
	return (i);
}


void	analyse_map_line(t_scene *scene, char *line, int line_num)
{
	(void)*scene;
	if (!does_line_contain_only_map_symbols(line))
	{
		printf("Error. Line %d contains unsupported characters.\n", line_num);
		scene->data_status = WRONG;
		return ;
	}
	scene->data_status = MAP_PROCESSING;
}

