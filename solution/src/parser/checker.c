/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:35:37 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/28 12:44:56 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "checker.h"

int	check_file_extantion(char *fname)
{
	int	len;

	len = ft_strlen(fname);
	if (fname[len - 4] == '.'
		&& fname[len - 3] == 'c'
		&& fname[len - 2] == 'u'
		&& fname[len - 1] == 'b')
		return (1);
	return (print_invalid_file_extension(), 0);
}

int	check_argument(int arg_count)
{
	if (arg_count == 0)
		return (print_no_argument(), 0);
	if (arg_count > 1)
		return (print_too_many_arguments(), 0);
	return (1);
}
