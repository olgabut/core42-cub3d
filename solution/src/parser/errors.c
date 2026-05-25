/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:43:02 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/25 09:27:47 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_no_argument(void)
{
	printf("Error\nNo argument. ");
	printf("Please provide one argument with the map file path.\n");
}

void	print_too_many_arguments(void)
{
	printf("Error\nToo many arguments. ");
	printf("Please provide only one argument with map file path.\n");
}

void	print_invalid_file_extension(void)
{
	printf("Error\nInvalid file extension. ");
	printf("The map file must have the .cub extension.\n");
}

void	print_file_not_found(void)
{
	printf("Error\nThe map file not found. ");
	printf("Please provide a valid path to an existing file.\n");
}
