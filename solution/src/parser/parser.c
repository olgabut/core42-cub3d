/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 11:59:36 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/22 12:14:16 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

/*
	Return
		1 - ok
		0 - some error (stop program)
*/
int	parser(t_input *input, int arg_count, char **argv, t_memory_info *memory)
{
	(void)*input;
	(void)*memory;
	(void)**argv;
	if (!check_argument(arg_count) || !check_file_extantion(argv[1]))
		return (0);
	
	return (1);
}