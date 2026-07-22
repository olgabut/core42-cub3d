/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/21 15:40:35 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	setup_line_bonus(t_graphics *g, t_trace *tr)
{
	t_vec	hit;
	int		map_x;
	int		map_y;

	hit = get_collide_pos(*tr);
	map_x = (int)hit.x;
	map_y = (int)hit.y;
	if (g->scene->map.map[map_y][map_x] == '2')
		tr->line.img = &(g->door);
	else
	{
		if ((tr->side == 'N' && g->scene->map.map[map_y + 1][map_x] == '2')
			|| (tr->side == 'S' && g->scene->map.map[map_y - 1][map_x] == '2')
			|| (tr->side == 'W' && g->scene->map.map[map_y][map_x + 1] == '2')
			|| (tr->side == 'E' && g->scene->map.map[map_y][map_x - 1] == '2'))
			tr->line.img = &(g->door);
		else
			tr->line.img = get_texture(g, tr->side);
	}
}
