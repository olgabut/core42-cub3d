/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:22:30 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/28 14:41:09 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_string(char *str)
{
	size_t	len;
	size_t	i;

	while (*str == ' ')
		str++;
	len = ft_strlen(str);
	if (len < 1)
		return (str);
	i = 0;
	if (str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
		i = 1;
	}
	while ((len > (i + 1)) && str[len - i - 1] == ' ')
		i++;
	str[len - i] = '\0';
	return (str);
}

void	save_texture(t_texture *where, char *what,
		char texture_name[3], int line_num)
{
	size_t	len;

	len = ft_strlen(what);
	if (len < 1)
		return ;
	if (where->texture != NULL)
		printf("Warning Line %d. Duplicate %s texture definition\n",
			line_num, texture_name);
	where->texture = what;
}

void	analyse_texture_info(t_scene *scene, char *line, int line_num)
{
	char	*trim_path;
	char	texture_name[3];
	size_t	len;

	texture_name[0] = line[0];
	texture_name[1] = line[1];
	texture_name[2] = '\0';
	if (line[2] != ' ')
		printf("Warning Line %d. No space after %s.\n", line_num, texture_name);
	trim_path = trim_string(line + 2);
	len = ft_strlen(trim_path);
	if (len < 1)
		printf("Warning Line %d. No file for texture %s.\n",
			line_num, texture_name);
	if (ft_strncmp(texture_name, "NO", 2) == 0)
		save_texture(&(scene->north), trim_path, texture_name, line_num);
	else if (ft_strncmp(texture_name, "SO", 2) == 0)
		save_texture(&(scene->south), trim_path, texture_name, line_num);
	else if (ft_strncmp(texture_name, "WE", 2) == 0)
		save_texture(&(scene->west), trim_path, texture_name, line_num);
	else if (ft_strncmp(texture_name, "EA", 2) == 0)
		save_texture(&(scene->east), trim_path, texture_name, line_num);
}

void	analyse_color_info(t_scene *scene, char *line, int line_num,
	t_memory_info **memory)
{
	char	*trim_value;
	size_t	len;
	// char	**colors;
	// int		i;

	(void)*memory;
	(void)*scene;
	// if (line[0] == 'C')
	// 	*surface = "ceiling";
	// else
	// 	*surface = "floor";
	if (line[1] != ' ')
		printf("Warning Line %d. No space after %c.\n", line_num, line[0]);
	trim_value = trim_string(line + 1);
	len = ft_strlen(trim_value);
	if (len < 1)
		printf("Warning Line %d. No info about color.\n", line_num);
	// colors = ft_split(trim_value, ',');
	// i = 0;
	// while (colors[i] != NULL)
	// {
	// 	printf("color [%d] = %s\n", i, colors[i]);
	// 	add_new_memory_link_for_control(memory, colors);
	// 	i++;
	// }
}
