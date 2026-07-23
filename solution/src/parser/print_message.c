/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:43:02 by obutolin          #+#    #+#             */
/*   Updated: 2026/07/23 11:21:22 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

void	print_no_texture(char cardinal_direction)
{
	ft_putstr_fd("Error\nNo texture specified for ", STDERR_FILENO);
	if (cardinal_direction == 'N')
		ft_putstr_fd("north (NO)", STDERR_FILENO);
	else if (cardinal_direction == 'S')
		ft_putstr_fd("south (SO)", STDERR_FILENO);
	else if (cardinal_direction == 'W')
		ft_putstr_fd("west (WE)", STDERR_FILENO);
	else if (cardinal_direction == 'E')
		ft_putstr_fd("east (EA)", STDERR_FILENO);
	else if (BONUS_MODE && cardinal_direction == 'D')
		ft_putstr_fd("door (D)", STDERR_FILENO);
	ft_putstr_fd(".\n", STDERR_FILENO);
}

void	print_common_error(enum e_error error)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (error == NO_ARGUMENT)
		ft_putstr_fd("No argument. Please provide one argument: file path", 2);
	else if (error == TOO_MANY_ARGUMENTS)
		ft_putstr_fd(
			"Too many arguments. Please provide one argument: file path", 2);
	else if (error == INVALID_FILE_EXTENTION)
		ft_putstr_fd(
			"Invalid file extension. The file must have '.cub' extension", 2);
	else if (error == FILE_NOT_FOUND)
		ft_putstr_fd(
			"The file not found. Provide a path to an existing file", 2);
	else if (error == MEMORY_ERROR)
		ft_putstr_fd("Memory problem", STDERR_FILENO);
	ft_putstr_fd(".\n", STDERR_FILENO);
}

void	print_file_content_error(enum e_file_content_error error,
	int line_num, char *spec)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (line_num >= 0)
		ft_fprintf(STDERR_FILENO, "Line %d. ", line_num);
	if (error == NO_TEXTURE)
		ft_fprintf(STDERR_FILENO, "No path for texture %s", spec);
	else if (error == MUPTIPLE_TEXTURE)
		ft_fprintf(STDERR_FILENO, "Multiple %s texture definition", spec);
	else if (error == MUPTIPLE_COLOR)
		ft_putstr_fd("Multiple color definitions", STDERR_FILENO);
	else if (error == WRONG_COLOR_VALUE)
		ft_putstr_fd(
			"Color value must be 3 numbers (0-255) separated by commas", 2);
	else if (error == UNSUPPORTED_CHARACTERS)
		ft_putstr_fd("The line contains unsupported characters", STDERR_FILENO);
	else if (error == MUPTIPLE_STARTING_POSITIONS)
	{
		ft_putstr_fd(
			"Multiple starting player positions on the map. Only one ", 2);
		ft_putstr_fd("character is allowed: N or S or E or W", STDERR_FILENO);
	}
	else if (error == NO_STARTING_POSITION)
		ft_putstr_fd("No player start position on the map", STDERR_FILENO);
	else if (error == NO_MAP)
		ft_putstr_fd("No map in the file", STDERR_FILENO);
	ft_putstr_fd(".\n", STDERR_FILENO);
}

void	print_file_content_warning(enum e_file_content_warning warning,
	int line_num, char *spec)
{
	ft_putstr_fd("Warning\n", STDERR_FILENO);
	if (warning == NO_SPACE)
		ft_fprintf(STDERR_FILENO,
			"Line %d. No space after identifier", line_num);
	else if (warning == NO_COLOR)
	{
		ft_fprintf(STDERR_FILENO, "No color information for the %s. ", spec);
		ft_fprintf(STDERR_FILENO,
			"The %s will be white (default value).", spec);
	}
	ft_putstr_fd(".\n", STDERR_FILENO);
}
