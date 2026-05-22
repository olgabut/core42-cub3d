/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 09:50:14 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/22 12:02:28 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
// # include "minilibx-linux/mlx.h"
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_texture
{
	char	*texture;
}	t_texture;

typedef struct s_map
{
	char	**map;
}	t_map;

typedef struct s_input
{
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
}	t_input;

int	parser(t_input *input, int arg_count, char **argv, t_memory_info *memory);

#endif
