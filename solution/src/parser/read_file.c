/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 09:25:16 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/21 12:27:42 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"
#include "analyzer.h"

static size_t	count_first_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

static void	analyse_line(t_scene *scene, char *line, int line_num)
{
	size_t	len;
	char	*no_spaces_line;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (scene->data_status == MAP_PROCESSING)
	{
		analyse_map_line(scene, line, line_num);
		return ;
	}
	no_spaces_line = line + count_first_spaces(line);
	if (ft_strlen(no_spaces_line) < 1)
		return ;
	if (no_spaces_line[0] == 'F' || no_spaces_line[0] == 'C')
		analyse_color(scene, no_spaces_line, line_num);
	else if (ft_strncmp(no_spaces_line, "NO", 2) == 0
		|| ft_strncmp(no_spaces_line, "SO", 2) == 0
		|| ft_strncmp(no_spaces_line, "WE", 2) == 0
		|| ft_strncmp(no_spaces_line, "EA", 2) == 0
		|| (BONUS_MODE && no_spaces_line[0] == 'D'))
		analyse_texture(scene, no_spaces_line, line_num);
	else
		analyse_map_line(scene, line, line_num);
}

/*
	Reads file <file_name> and fills out a <scene_data> struct
	Return
		0 - error (stop program)
		1 - ok
*/
int	read_file(t_scene *scene, char *file_name)
{
	int		fd;
	char	*line;
	int		line_number;

	fd = open(file_name, O_RDONLY | O_RDWR);
	if (fd < 0)
		return (print_common_error(FILE_NOT_FOUND), 0);
	line_number = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		add_new_memory_link_for_control(&scene->memory, line);
		if (scene->data_status != WRONG)
			analyse_line(scene, line, line_number);
		line_number++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
