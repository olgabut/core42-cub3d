/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:43:02 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/09 12:34:47 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

void	print_no_texture(char cardinal_direction)
{
	printf("Error\nNo texture specified for ");
	if (cardinal_direction == 'N')
		printf("north (NO)");
	else if (cardinal_direction == 'S')
		printf("south (SO)");
	else if (cardinal_direction == 'W')
		printf("west (WE)");
	else if (cardinal_direction == 'E')
		printf("east (EA)");
	printf(".\n");
}

void	print_common_error(enum e_error error)
{
	printf("Error\n");
	if (error == NO_ARGUMENT)
		printf("No argument. Please provide one argument: file path");
	else if (error == TOO_MANY_ARGUMENTS)
		printf("Too many arguments. Please provide one argument: file path");
	else if (error == INVALID_FILE_EXTENTION)
		printf("Invalid file extension. The file must have '.cub' extension");
	else if (error == FILE_NOT_FOUND)
		printf("The file not found. Provide a path to an existing file");
	else if (error == MEMORY_ERROR)
		printf("Memory problem");
	printf(".\n");
}

void	print_file_content_error(enum e_file_content_error error,
	int line_num, char *spec)
{
	printf("Error\n");
	if (line_num >= 0)
		printf("Line %d. ", line_num);
	if (error == NO_TEXTURE)
		printf("No path for texture %s", spec);
	else if (error == MUPTIPLE_TEXTURE)
		printf("Multiple %s texture definition", spec);
	else if (error == MUPTIPLE_COLOR)
		printf("Multiple color definitions");
	else if (error == WRONG_COLOR_VALUE)
		printf("Color value must be 3 numbers (0-255) separated by commas");
	else if (error == UNSUPPORTED_CHARACTERS)
		printf("The line contains unsupported characters");
	else if (error == MUPTIPLE_STARTING_POSITIONS)
	{
		printf("Multiple starting player positions on the map. ");
		printf("Only one character is allowed: N or S or E or W");
	}
	else if (error == NO_STARTING_POSITION)
		printf("No player start position on the map (N, S, W, E)");
	else if (error == NO_MAP)
		printf("No map in the file");
	printf(".\n");
}

void	print_file_content_warning(enum e_file_content_warning warning,
	int line_num, char *spec)
{
	printf("Warning\n");
	if (warning == NO_SPACE)
		printf("Line %d. No space after identifier", line_num);
	else if (warning == NO_COLOR)
	{
		printf("No color information for the %s. ", spec);
		printf("The %s will be white (default value).", spec);
	}
	printf(".\n");
}
