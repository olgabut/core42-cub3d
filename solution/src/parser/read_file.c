/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 09:25:16 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/27 09:04:56 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

int	analyse_line(t_scene *scene, char *line, t_memory_info *memory)
{
	(void)*scene;
	char *trim_line;

	trim_line = ft_strtrim(line, " ");
	if (ft_strncmp(trim_line, "NO", 2) || ft_strncmp(trim_line, "SO", 2)
		|| (ft_strncmp(trim_line, "WE", 2) || ft_strncmp(trim_line, "EA", 2)))
		printf("texture\n");
	else if (ft_strncmp(trim_line, "F", 1) || ft_strncmp(trim_line, "C", 1))
		printf("color\n");
	free(trim_line);
	return (1);
}

/*
	Reads file <file_name> and fills out a <scene_data> struct
	Return
		0 - error (stop program)
		1 - ok
*/
int	read_file(t_scene *scene, char *file_name, t_memory_info *memory)
{
	int	fd;
	char *line;

	fd = open(file_name, O_RDONLY | O_RDWR);
	if (fd < 0)
		return (print_file_not_found(), 0);
	while ((line = get_next_line(fd)) != NULL)
	{
		analyse_line(scene, line, memory);
		free(line);
	}
	close(fd);
	return (1);
}
