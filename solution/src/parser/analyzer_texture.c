/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:22:30 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/28 11:22:51 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

/*
	Return
		1 - ok (saved)
		0 - error
*/
static int	save_texture(t_texture *where, char *what,
		char texture_id[3], int line_num)
{
	if (where->texture != NULL)
	{
		print_file_content_error(MUPTIPLE_TEXTURE, line_num, texture_id);
		return (0);
	}
	where->texture = what;
	return (1);
}

static int	is_texture_value(t_scene *scene, char *value, char texture_id[3],
	int line_num)
{
	size_t	len;

	len = ft_strlen(value);
	if (len < 1)
	{
		print_file_content_error(NO_TEXTURE, line_num, texture_id);
		scene->data_status = WRONG;
		return (0);
	}
	return (1);
}

void	analyse_texture(t_scene *scene, char *line, int line_num)
{
	char	*trim_path;
	char	texture_id[3];
	int		status;

	texture_id[0] = line[0];
	texture_id[1] = line[1];
	texture_id[2] = '\0';
	if (line[2] != ' ' && line[0] != 'D')
		print_file_content_warning(NO_SPACE, line_num, "");
	trim_path = ft_strtrim_changed(line + 2);
	if (!is_texture_value(scene, trim_path, texture_id, line_num))
		return ;
	status = 1;
	if (ft_strncmp(texture_id, "NO", 2) == 0)
		status = save_texture(&(scene->north), trim_path, texture_id, line_num);
	else if (ft_strncmp(texture_id, "SO", 2) == 0)
		status = save_texture(&(scene->south), trim_path, texture_id, line_num);
	else if (ft_strncmp(texture_id, "WE", 2) == 0)
		status = save_texture(&(scene->west), trim_path, texture_id, line_num);
	else if (ft_strncmp(texture_id, "EA", 2) == 0)
		status = save_texture(&(scene->east), trim_path, texture_id, line_num);
	else if (BONUS_MODE && line[0] == 'D')
		status = save_texture(&(scene->door), trim_path, "door", line_num);
	if (!status)
		scene->data_status = WRONG;
}
