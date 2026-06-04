/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 09:25:16 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/04 07:47:13 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"
#include "analyzer.h"

int	analyse_line(t_scene *scene, char *line, int line_num)
{
	char	*trimed_line;

	printf("'%s'", line);
	trimed_line = ft_strtrim(line, " ");
	add_new_memory_link_for_control(&scene->memory, trimed_line);
	if (trimed_line[0] == 'F' || trimed_line[0] == 'C')
		analyse_color(scene, trimed_line, line_num);
	else if (ft_strncmp(trimed_line, "NO", 2) == 0
		|| ft_strncmp(trimed_line, "SO", 2) == 0
		|| ft_strncmp(trimed_line, "WE", 2) == 0
		|| ft_strncmp(trimed_line, "EA", 2) == 0)
		analyse_texture(scene, trimed_line, line_num);
	else
	{
		analyse_map_line(scene, line, line_num);
		//printf("map\n");
	}
	return (1);
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
		return (print_file_not_found(), 0);
	line_number = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		analyse_line(scene, line, line_number);
		line_number++;
		free(line);
		printf("\n");
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
