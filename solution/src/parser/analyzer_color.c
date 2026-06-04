/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:03:11 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/04 14:45:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_dig_color(int *dig, char *value)
{
	int	dig_value;

	if (!ft_strtoint(&dig_value, ft_strtrim_changed(value)))
		return (0);
	if (dig_value < 0 || dig_value > 255)
		return (0);
	*dig = dig_value;
	return (1);
}

int	save_colors(t_color *surface, char **cols)
{
	int	i;
	int	dig_value[3];

	i = 0;
	while (i < 3)
	{
		if (!get_dig_color(&dig_value[i], cols[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		surface->color[i] = dig_value[i];
		i++;
	}
	return (1);
}

void	analyse_color(t_scene *scene, char *line, int line_num)
{
	char	**cols;
	int		i;
	int		wrong;
	t_color	*surface;

	if (line[0] == 'C')
		surface = &(scene->ceiling);
	else
		surface = &(scene->floor);
	if (surface->color[0] != -1)
	{
		printf("Error\nLine %d. Duplicate color definition.\n", line_num);
		scene->data_status = WRONG;
		return ;
	}
	if (line[1] != ' ')
		printf("Warning Line %d. No space after %c.\n", line_num, line[0]);
	cols = ft_split(line + 1, ',');
	add_new_memory_link_for_control(&scene->memory, cols);
	i = 0;
	while (cols[i] != NULL)
		add_new_memory_link_for_control(&scene->memory, cols[i++]);
	wrong = i != 3;
	if (wrong || !save_colors(surface, cols))
	{
		printf("Error\nLine %d. Wrong color value.", line_num);
		scene->data_status = WRONG;
	}
}
