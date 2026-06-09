/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 09:50:14 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/09 09:51:54 by obutolin         ###   ########.fr       */
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
	int	color[3];
}	t_color;

typedef struct s_texture
{
	char	*texture;
}	t_texture;

typedef struct s_map_list
{
	struct s_map_list	*next;
	char				*line;
}						t_map_list;

//player_orientation can be 'N','S','E' or 'W'
typedef struct s_map
{
	int			first_line_in_file;
	int			last_line_in_file;
	int			player_position_x;
	int			player_position_y;
	char		player_orientation;
	t_map_list	*map_list_header;
	char		**map;
	size_t		size_x;
	size_t		size_y;
}				t_map;

enum e_status
{
	OK,
	WRONG,
	MAP_PROCESSING
};

typedef struct s_scene
{
	t_memory_info	*memory;
	enum e_status	data_status;
	t_texture		north;
	t_texture		south;
	t_texture		west;
	t_texture		east;
	t_color			floor;
	t_color			ceiling;
	t_map			map;
}	t_scene;

int	parser(t_scene *scene, int arg_count, char **argv);

#endif
