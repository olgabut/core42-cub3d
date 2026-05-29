/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:22:30 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/29 12:11:46 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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
	trim_path = ft_strtrim_changed(line + 2);
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


