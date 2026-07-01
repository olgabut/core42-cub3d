/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:14:42 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/29 12:40:08 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"
#include "analyzer.h"

static int	flood_fill(char **map, int x, int y)
{
	if (!map[y] || !map[y][x])
	{
		printf("Error\nThe game space is not enclosed (%d, %d).\n", x, y);
		return (0);
	}
	if (map[y][x] == '1')
		return (1);
	if (map[y][x] != '0')
	{
		printf("Error\nThere are unresolved cherecters on the map (%d, %d).\n",
			x, y);
		return (0);
	}
	map[y][x] = '1';
	if (!flood_fill(map, x + 1, y))
		return (0);
	if (!flood_fill(map, x - 1, y))
		return (0);
	if (!flood_fill(map, x, y + 1))
		return (0);
	if (!flood_fill(map, x, y - 1))
		return (0);
	return (1);
}

/*
	Return
		1 - 0k
		0 - error
*/
int	check_map_array(t_scene *scene)
{
	char	**copy;

	copy = NULL;
	if (!copy_map_array(&copy, scene))
	{
		print_common_error(MEMORY_ERROR);
		return (0);
	}
	copy[scene->map.player_position_y][scene->map.player_position_x] = '0';
	if (!flood_fill(copy,
			scene->map.player_position_x, scene->map.player_position_y))
		return (0);
	return (1);
}
