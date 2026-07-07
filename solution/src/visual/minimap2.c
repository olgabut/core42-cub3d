#include "renderer.h"

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

void	mm_draw_bg(t_image *s)
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

static void	draw_arrow_body(t_image *s, int cx, int cy, double angle)
{
	int		i;
	double	t;
	int		dx;
	int		dy;

	i = 0;
	while (i <= 16)
	{
		t = (double)i / 16;
		dx = (int)(cx + t * ((cx + cos(angle) * 8.0) - cx));
		dy = (int)(cy + t * ((cy + sin(angle) * 8.0) - cy));
		put_pixel(s, dx, dy, 0xFF7777);
		i++;
	}
}

static void	put_pixel_by_dx_dy(t_image *s, int dx, int dy)
{
	put_pixel(s, dx, dy, 0xFF4444);
	put_pixel(s, dx + 1, dy, 0xFF4444);
	put_pixel(s, dx, dy + 1, 0xFF4444);
}

/*
	tip_x = cx + cos(angle) * 8.0;
	tip_y = cy + sin(angle) * 8.0;
	lx = cx + cos(angle + 2.4) * 5.0;
	ly = cy + sin(angle + 2.4) * 5.0;
	rx = cx + cos(angle - 2.4) * 5.0;
	ry = cy + sin(angle - 2.4) * 5.0;
*/
void	mm_draw_arrow(t_image *s, int cx, int cy, double angle)
{
	int		dx;
	int		dy;
	int		i;

	i = 0;
	while (i <= 16)
	{
		dx = (int)((cx + cos(angle + 2.4) * 5.0)
				+ ((double)i / 16) * ((cx + cos(angle) * 8.0)
					- (cx + cos(angle + 2.4) * 5.0)));
		dy = (int)((cy + sin(angle + 2.4) * 5.0)
				+ ((double)i / 16) * ((cy + sin(angle) * 8.0)
					- (cy + sin(angle + 2.4) * 5.0)));
		put_pixel_by_dx_dy(s, dx, dy);
		dx = (int)((cx + cos(angle - 2.4) * 5.0)
				+ ((double)i / 16) * ((cx + cos(angle) * 8.0)
					- (cx + cos(angle - 2.4) * 5.0)));
		dy = (int)((cy + sin(angle - 2.4) * 5.0)
				+ ((double)i / 16) * ((cy + sin(angle) * 8.0)
					- (cy + sin(angle - 2.4) * 5.0)));
		put_pixel_by_dx_dy(s, dx, dy);
		i++;
	}
	draw_arrow_body(s, cx, cy, angle);
}
