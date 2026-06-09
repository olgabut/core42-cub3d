/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:03:11 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/09 11:40:33 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

static int	get_dig_color(int *dig, char *value)
{
	int	dig_value;

	if (!ft_strtoint(&dig_value, ft_strtrim_changed(value)))
		return (0);
	if (dig_value < 0 || dig_value > 255)
		return (0);
	*dig = dig_value;
	return (1);
}

static int	save_colors(t_color *surface, char **cols)
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

static char	**split_color_value(t_scene *scene, char *line, int *cols_count)
{
	char	**cols;
	int		i;

	cols = ft_split(line + 1, ',');
	add_new_memory_link_for_control(&scene->memory, cols);
	i = 0;
	while (cols[i] != NULL)
		add_new_memory_link_for_control(&scene->memory, cols[i++]);
	*cols_count = i;
	return (cols);
}

void	analyse_color(t_scene *scene, char *line, int line_num)
{
	char	**cols;
	int		cols_count;
	t_color	*surface;

	if (line[0] == 'C')
		surface = &(scene->ceiling);
	else
		surface = &(scene->floor);
	if (surface->color[0] != -1)
	{
		print_file_content_error(MUPTIPLE_COLOR, line_num, "");
		scene->data_status = WRONG;
		return ;
	}
	if (line[1] != ' ')
		print_file_content_warning(NO_SPACE, line_num, "");
	cols_count = 0;
	cols = split_color_value(scene, line, &cols_count);
	if (cols_count != 3 || !save_colors(surface, cols))
	{
		print_file_content_error(WRONG_COLOR_VALUE, line_num, "");
		scene->data_status = WRONG;
	}
}
