/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:03:11 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/29 12:35:55 by obutolin         ###   ########.fr       */
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

int	save_colors(t_scene *scene, char surface, int line_num, char **cols)
{
	int	i;
	int	dig_value[3];

	i = 0;
	while (i < 3)
	{
		if (get_dig_color())
		i++;
	}
	if (color->color[i] != -1)
	{
		printf("Warning Line %d. Duplicate color definition\n", line_num);
		return (0);
	}
	color = dig_value;
	return (1);
}

void	analyse_color_info(t_scene *scene, char *line, int line_num,
	t_memory_info **memory)
{
	char	**cols;
	int		i;
	int		wrong;

	(void)*scene;
	if (line[1] != ' ')
		printf("Warning Line %d. No space after %c.\n", line_num, line[0]);
	cols = ft_split(line + 1, ',');
	add_new_memory_link_for_control(memory, cols);
	i = 0;
	wrong = false;
	while (cols[i] != NULL)
	{
		add_new_memory_link_for_control(memory, cols[i]);
		wrong = i > 2;
		i++;
	}
	// (!save_a_color(&(scene->ceiling), line_num, i, cols[i]));
	if (wrong || !save_colors(scene, line[0], line_num, cols))
	{
		printf("Warning Line %d. Wrong color value.", line_num);
		return ;
	}
}
