/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:14:42 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/29 11:47:49 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"
#include "analyzer.h"

/*
	Return
		1 - 0k
		0 - error
*/
int	check_map_array(t_scene *scene)
{
	char **copy;

	printf("check_map_array\n");
	copy = NULL;
	if (!copy_map_array(&copy, scene))
	{
		print_common_error(MEMORY_ERROR);
		return (0);
	}
	print_map_array(copy);
	return (1);
}

