#include "renderer.h"

static void	mm_fill_rect(t_image *s, int px, int py, int sz, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < sz)
	{
		dx = 0;
		while (dx < sz)
		{
			put_pixel(s, px + dx, py + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	mm_draw_border(t_image *s)
{
	int	i;

	i = MM_X - MM_PADDING;
	while (i < MM_X + MM_VIEW + MM_PADDING)
	{
		put_pixel(s, i, MM_Y - MM_PADDING, 0x555566);
		put_pixel(s, i, MM_Y + MM_VIEW + MM_PADDING - 1, 0x555566);
		i++;
	}
	i = MM_Y - MM_PADDING;
	while (i < MM_Y + MM_VIEW + MM_PADDING)
	{
		put_pixel(s, MM_X - MM_PADDING, i, 0x555566);
		put_pixel(s, MM_X + MM_VIEW + MM_PADDING - 1, i, 0x555566);
		i++;
	}
}

static void	mm_draw_bg(t_image *s)
{
	int	x;
	int	y;

	y = MM_Y - MM_PADDING;
	while (y < MM_Y + MM_VIEW + MM_PADDING)
	{
		x = MM_X - MM_PADDING;
		while (x < MM_X + MM_VIEW + MM_PADDING)
		{
			put_pixel(s, x, y, 0x111122);
			x++;
		}
		y++;
	}
	mm_draw_border(s);
}

static void	mm_draw_arrow(t_image *s, int cx, int cy, double angle)
{
	double	tip_x;
	double	tip_y;
	double	lx;
	double	ly;
	double	rx;
	double	ry;
	int		dx;
	int		dy;
	int		i;
	double	t;

	tip_x = cx + cos(angle) * 8.0;
	tip_y = cy + sin(angle) * 8.0;
	lx = cx + cos(angle + 2.4) * 5.0;
	ly = cy + sin(angle + 2.4) * 5.0;
	rx = cx + cos(angle - 2.4) * 5.0;
	ry = cy + sin(angle - 2.4) * 5.0;
	i = 0;
	while (i <= 16)
	{
		t = (double)i / 16;
		dx = (int)(lx + t * (tip_x - lx));
		dy = (int)(ly + t * (tip_y - ly));
		put_pixel(s, dx, dy, 0xFF4444);
		put_pixel(s, dx + 1, dy, 0xFF4444);
		put_pixel(s, dx, dy + 1, 0xFF4444);
		dx = (int)(rx + t * (tip_x - rx));
		dy = (int)(ry + t * (tip_y - ry));
		put_pixel(s, dx, dy, 0xFF4444);
		put_pixel(s, dx + 1, dy, 0xFF4444);
		put_pixel(s, dx, dy + 1, 0xFF4444);
		i++;
	}
	i = 0;
	while (i <= 16)
	{
		t = (double)i / 16;
		dx = (int)(cx + t * (tip_x - cx));
		dy = (int)(cy + t * (tip_y - cy));
		put_pixel(s, dx, dy, 0xFF7777);
		i++;
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
	if (cell == ' ' || cell == '\t' || cell == '\0')
		return (0x111122);
	return (0x2d2d44);
}

void	draw_minimap(t_graphics *g)
{
	int	cam_x;
	int	cam_y;
	int	tiles;
	int	tx;
	int	ty;
	int	player_px;
	int	player_py;

	size_t	i = 0;
	while (i < g->scene->map.size_y)
		i++;
	get_cam_offset(g, &cam_x, &cam_y);
	mm_draw_bg(&g->screen);
	tiles = MM_VIEW / MM_SCALE;
	ty = 0;
	while (ty < tiles)
	{
		tx = 0;
		while (tx < tiles)
		{
			mm_fill_rect(&g->screen,
				MM_X + tx * MM_SCALE,
				MM_Y + ty * MM_SCALE,
				MM_SCALE - 1,
				get_tile_color(g, cam_x + tx, cam_y + ty));
			tx++;
		}
		ty++;
	}
	player_px = MM_X + (int)(((g->player.x / 64.0) - cam_x) * MM_SCALE);
	player_py = MM_Y + (int)(((g->player.y / 64.0) - cam_y) * MM_SCALE);
	mm_draw_arrow(&g->screen, player_px, player_py, g->player.angle);
}
