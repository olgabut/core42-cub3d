/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:14:42 by obutolin          #+#    #+#             */
/*   Updated: 2026/08/03 14:41:11 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"
#include "analyzer.h"

static void	print_unresolved_charecters(int x, int y)
{
	ft_fprintf(STDERR_FILENO,
		"Error\nThere are unresolved cherecters on the map (%d, %d).\n",
		x, y);
}

static int	flood_fill(char **map, int x, int y, t_scene *scene)
{
	if ( x < 0 || x >= (int)scene->map.size_x
		|| y < 0 || y >= (int)scene->map.size_y
		|| !map[y] || !map[y][x])
	{
		ft_putstr_fd("Error\nThe game space on the map is not enclosed.\n",
			STDERR_FILENO);
		return (0);
	}
	if (map[y][x] == '1')
		return (1);
	if (BONUS_MODE && map[y][x] != '0' && map[y][x] != '2' && map[y][x] != '3')
		return (print_unresolved_charecters(x, y), 0);
	else if (!BONUS_MODE && map[y][x] != '0')
		return (print_unresolved_charecters(x, y), 0);
	map[y][x] = '1';
	if (!flood_fill(map, x + 1, y, scene))
		return (0);
	if (!flood_fill(map, x - 1, y, scene))
		return (0);
	if (!flood_fill(map, x, y + 1, scene))
		return (0);
	if (!flood_fill(map, x, y - 1, scene))
		return (0);
	return (1);
}

static void	rewrite_map(char ***copy, t_map map)
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

static int	check_doors(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == '7')
		return (1);
	if (map[y][x] == '2'
			&& !(((map[y - 1][x] == '0' || map[y - 1][x] == '7'
					|| map[y - 1][x] == '3')
			&& (map[y + 1][x] == '0' || map[y + 1][x] == '7'
				|| map[y + 1][x] == '3')
			&& map[y][x - 1] == '1' && map[y][x + 1] == '1')
		||
			((map[y][x - 1] == '0' || map[y][x - 1] == '7'
				|| map[y][x - 1] == '3')
			&& (map[y][x + 1] == '0' || map[y][x + 1] == '7'
				|| map[y][x + 1] == '3')
			&& map[y - 1][x] == '1' && map[y + 1][x] == '1')))
	{
		ft_fprintf(STDERR_FILENO,
			"Error\nInvalid door position (%d, %d).\n", x, y);
		return (0);
	}
	map[y][x] = '7';
	if (!check_doors(map, x + 1, y) || !check_doors(map, x - 1, y)
		|| !check_doors(map, x, y + 1) || !check_doors(map, x, y - 1))
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
			scene->map.player_position_x,
			scene->map.player_position_y,
			scene))
		return (0);
	if (BONUS_MODE)
	{
		rewrite_map(&copy, scene->map);
		copy[scene->map.player_position_y][scene->map.player_position_x] = '0';
		if (!check_doors(copy,
				scene->map.player_position_x, scene->map.player_position_y))
			return (0);
	}
	return (1);
}
