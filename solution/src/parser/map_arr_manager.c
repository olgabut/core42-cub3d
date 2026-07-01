/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_arr_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 12:06:33 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/29 12:09:03 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_row_to_arr(t_scene *scene, char **map, char *line, size_t i)
{
	size_t		j;
	size_t		list_line_len;

	j = 0;
	list_line_len = ft_strlen(line);
	while (j < scene->map.size_x)
	{
		if (list_line_len > j)
			map[i][j] = line[j];
		else
			map[i][j] = ' ';
		j++;
	}
}

int	conver_map_list_to_arr(t_scene *scene)
{
	char		**map;
	t_map_list	*list_line;
	size_t		i;

	map = malloc((scene->map.size_y + 1) * sizeof(char *));
	if (!map)
		return (0);
	add_new_memory_link_for_control(&scene->memory, map);
	i = 0;
	list_line = scene->map.map_list_header;
	while (i < scene->map.size_y)
	{
		map[i] = malloc((scene->map.size_x + 1) * sizeof(char));
		if (!map[i])
			return (0);
		add_new_memory_link_for_control(&scene->memory, map[i]);
		set_row_to_arr(scene, map, list_line->line, i);
		map[i][scene->map.size_x] = '\0';
		list_line = list_line->next;
		i++;
	}
	map[scene->map.size_y] = NULL;
	scene->map.map = map;
	return (1);
}

int	copy_map_array(char ***copy, t_scene *scene)
{
	char	**map;
	size_t	i;

	map = malloc((scene->map.size_y + 1) * sizeof(char *));
	if (!map)
		return (0);
	add_new_memory_link_for_control(&scene->memory, map);
	i = 0;
	while (i < scene->map.size_y)
	{
		map[i] = malloc((scene->map.size_x + 1) * sizeof(char));
		if (!map[i])
			return (0);
		add_new_memory_link_for_control(&scene->memory, map[i]);
		map[i] = ft_strdup(scene->map.map[i]);
		i++;
	}
	map[scene->map.size_y] = NULL;
	*copy = map;
	return (1);
}

void	print_map_array(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%zu '", i);
		j = 0;
		while (map[i][j] != '\0')
			printf("%c", map[i][j++]);
		i++;
		printf("'\n");
	}
}
