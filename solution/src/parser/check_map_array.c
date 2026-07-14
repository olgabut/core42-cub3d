/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:14:42 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/08 14:17:20 by obutolin         ###   ########.fr       */
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
	#ifdef BONUS
	if (map[y][x] != '0' && map[y][x] != '2')
	#else
	if (map[y][x] != '0')
	#endif
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

#ifdef BONUS
static void rewrite_map(char ***copy, t_map map)
{
	size_t	i;
	size_t	j;
	char	**newmap;

	newmap = *copy;
	i = 0;
	while (i < map.size_y)
	{
		j = 0;
		while (j < map.size_x)
		{
			newmap[i][j] = map.map[i][j];
			j++;
		}
		i++;
	}
}

static int check_doors(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == '7')
		return (1);
	if (map[y][x] == '2'
		&& !(((map[y - 1][x] == '0' || map[y - 1][x] == '7')
			&& (map[y + 1][x] == '0' || map[y + 1][x] == '7')
			&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
		||
		((map[y][x - 1] == '0' || map[y][x - 1] == '7')
			&& (map[y][x + 1] == '0' || map[y][x + 1] == '7')
			&& map[y - 1][x] == '1' && map[y + 1][x] == '1')))
	{
		printf("Error\nInvalid door position (%d, %d).\n", x, y);
		return (0);
	}
	map[y][x] = '7';
	if (!check_doors(map, x + 1, y))
		return (0);
	if (!check_doors(map, x - 1, y))
		return (0);
	if (!check_doors(map, x, y + 1))
		return (0);
	if (!check_doors(map, x, y - 1))
		return (0);
	return (1);
}
#endif

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
	#ifdef BONUS
	rewrite_map(&copy, scene->map);
	if (!check_doors(copy,
		scene->map.player_position_x, scene->map.player_position_y))
		return (0);
	#endif
	return (1);
}
