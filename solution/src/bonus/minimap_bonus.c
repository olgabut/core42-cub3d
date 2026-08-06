/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/21 15:08:07 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

static void	mm_fill_rect(t_image *s, int px, int py, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < MM_SCALE - 1)
	{
		dx = 0;
		while (dx < MM_SCALE - 1)
		{
			put_pixel(s, px + dx, py + dy, color);
			dx++;
		}
		dy++;
	}
}

static int	get_map_max_width(t_graphics *g)
{
	size_t	y;
	int		max;
	int		len;

	max = 0;
	y = 0;
	while (y < g->scene->map.size_y)
	{
		len = (int)ft_strlen(g->scene->map.map[y]);
		if (len > max)
			max = len;
		y++;
	}
	return (max);
}

static void	get_cam_offset(t_graphics *g, int *cam_x, int *cam_y)
{
	int	tiles;
	int	map_w;
	int	map_h;
	int	max_cam_x;
	int	max_cam_y;

	tiles = MM_VIEW / MM_SCALE;
	map_w = get_map_max_width(g);
	map_h = (int)g->scene->map.size_y;
	*cam_x = (int)(g->player.x / 64.0) - tiles / 2;
	*cam_y = (int)(g->player.y / 64.0) - tiles / 2;
	if (*cam_x < 0)
		*cam_x = 0;
	if (*cam_y < 0)
		*cam_y = 0;
	max_cam_x = map_w - tiles;
	max_cam_y = map_h - tiles;
	if (max_cam_x > 0 && *cam_x > max_cam_x)
		*cam_x = max_cam_x;
	if (max_cam_y > 0 && *cam_y > max_cam_y)
		*cam_y = max_cam_y;
}

static int	get_tile_color(t_graphics *g, int mx, int my)
{
	char	cell;
	int		row_len;

	if (my < 0 || my >= (int)g->scene->map.size_y)
		return (0x111122);
	row_len = (int)ft_strlen(g->scene->map.map[my]);
	if (mx < 0 || mx >= row_len)
		return (0x111122);
	cell = g->scene->map.map[my][mx];
	if (cell == '1')
		return (0x7a7a9a);
	if (cell == '2' && g->door_state[my][mx] == 0)
		return (0xc47a2a);
	if (cell == '2' && g->door_state[my][mx] == 1)
		return (0x5a3010);
	if (cell == '3')
		return (0xdd0000);
	if (cell == ' ' || cell == '\t' || cell == '\0')
		return (0x111122);
	return (0x2d2d44);
}

void	draw_minimap(t_graphics *g)
{
	int	cam_x;
	int	cam_y;
	int	tx;
	int	ty;

	get_cam_offset(g, &cam_x, &cam_y);
	mm_draw_bg(&g->screen);
	ty = 0;
	while (ty < MM_VIEW / MM_SCALE)
	{
		tx = 0;
		while (tx < MM_VIEW / MM_SCALE)
		{
			mm_fill_rect(&g->screen,
				MM_X + tx * MM_SCALE,
				MM_Y + ty * MM_SCALE,
				get_tile_color(g, cam_x + tx, cam_y + ty));
			tx++;
		}
		ty++;
	}
	mm_draw_arrow(&g->screen,
		MM_X + (int)(((g->player.x / 64.0) - cam_x) * MM_SCALE),
		MM_Y + (int)(((g->player.y / 64.0) - cam_y) * MM_SCALE),
		g->player.angle);
}
