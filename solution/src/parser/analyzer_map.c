/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:21:21 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/04 07:43:22 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Return
		line_len - it looks like a map line (return line_len)
		0 - it's not a map line
*/
int	is_map_line(char *line, int line_num)
{
	int	i;
	int	player_symbol_index;

	(void)line_num;
	i = 0;
	player_symbol_index = -1;
	while (line[i] != '\0')
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (player_symbol_index == -1)
				player_symbol_index = i;
			else
				// more then 1 player symbol in line
				printf("Error. The wrong map. there must be only one player symbol.\n");
				return (0);
		}
		else if (line[i] != ' ' && line[i] != '\n'
			&& line[i] != '0' && line[i] != '1')
		{
			//wrong symbol
			return (0);
		}
		i++;
	}
	return (i);
}

void	analyse_map_line(t_scene *scene, char *line, int line_num)
{
	(void)*scene;
	if (!is_map_line(line, line_num))
	{
		printf("It's not a map line %d\n", line_num);
		return ;
	}
	else
	{
		printf("It looks lika a map %d\n", line_num);
	}
}

