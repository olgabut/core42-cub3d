/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:47:02 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/29 11:42:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

enum e_error
{
	NO_ARGUMENT,
	TOO_MANY_ARGUMENTS,
	INVALID_FILE_EXTENTION,
	FILE_NOT_FOUND,
	MEMORY_ERROR
};

enum e_file_content_error
{
	NO_TEXTURE,
	MUPTIPLE_TEXTURE,
	MUPTIPLE_COLOR,
	WRONG_COLOR_VALUE,
	UNSUPPORTED_CHARACTERS,
	MUPTIPLE_STARTING_POSITIONS,
	NO_STARTING_POSITION,
	NO_MAP
};

enum e_file_content_warning
{
	NO_SPACE,
	NO_COLOR
};

int		check_argument(int arg_count);
int		check_file_extantion(char *fname);
int		check_struct_from_file(t_scene *scene);
int		check_map_from_file(t_scene *scene);
void	print_common_error(enum e_error error);
void	print_file_content_error(enum e_file_content_error error,
			int line_num, char *spec);
void	print_file_content_warning(enum e_file_content_warning warning,
			int line_num, char *spec);
void	print_no_texture(char cardinal_direction);
int	    check_map_array(t_scene *scene);

#endif