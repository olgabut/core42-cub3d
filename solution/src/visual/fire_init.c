#include "renderer.h"
#include <sys/time.h>

int	init_fire_texture(t_graphics *graphics)
{
	if (!load_texture(graphics, &graphics->fire_frames[0],
		"./scenes/texture/fire/fire01.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[1],
		"./scenes/texture/fire/fire02.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[2],
		"./scenes/texture/fire/fire03.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[3],
		"./scenes/texture/fire/fire04.xpm"))
		return (0);
	if (!load_texture(graphics, &graphics->fire_frames[4],
		"./scenes/texture/fire/fire05.xpm"))
		return (0);
	return (1);
}

void	free_fire_img(t_graphics *graphics)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (graphics->fire_frames[i].ptr)
			mlx_destroy_image(graphics->mlx, graphics->fire_frames[i].ptr);
		i++;
	}
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	update_fire(t_graphics *g)
{
	long	now;

	now = get_time_ms();
	if (now - g->fire_last_time > 200)
	{
		g->fire_frame = (g->fire_frame + 1) % 5;
		g->fire_last_time = now;
		g->moved = 1;
	}
}

void	draw_fire(t_graphics *g)
{
	int		x;
	int		y;
	double	dx;
	double	dy;
	double	dist;
	double	screen_x;
	int		size;
	double fov;
	double forward;
	double side;

	y = -1;
	fov = atan2(0.5, (double)WINDOW_HEIGHT / WINDOW_WIDTH);
	while (++y < (int)g->scene->map.size_y)
	{
		x = -1;
		while (++x < (int)g->scene->map.size_x)
		{
			if (g->scene->map.map[y][x] != '3')
				continue ;

			dx = (x * 64 + 32) - g->player.x;
			dy = (y * 64 + 32) - g->player.y;

			dist = sqrt(dx * dx + dy * dy)/64.0;
			forward = dx * cos(g->player.angle) + dy * sin(g->player.angle);
			side = -dx * sin(g->player.angle) + dy * cos(g->player.angle);
			if (forward <= 0)
				continue;
			screen_x = WINDOW_WIDTH / 2 + (side / forward)
				* (WINDOW_WIDTH / (2 * tan(fov)));

			size = (int)(WINDOW_HEIGHT / (dist * 0.8));

			t_shape shape;
			shape.x = (int)screen_x - size / 2;
			shape.y = (WINDOW_HEIGHT - size) / 2;
			shape.width = size;
			shape.height = size;
			shape.img = &g->fire_frames[g->fire_frame];

			draw_sprite(g, shape);
		}
	}
}

void	draw_sprite(t_graphics *g, t_shape s)
{
	int	x;
	int	y;
	int	color;
	int	tex_x;
	int	tex_y;

	y = 0;
	while (y < s.height)
	{
		int screen_y = s.y + y;
		if (screen_y < 0 || screen_y >= WINDOW_HEIGHT)
		{
			y++;
			continue;
		}

		tex_y = (y * s.img->height) / s.height;

		x = 0;
		while (x < s.width)
		{
			int screen_x = s.x + x;
			if (screen_x >= 0 && screen_x < WINDOW_WIDTH)
			{
				tex_x = (x * s.img->width) / s.width;
				color = get_pixel(s.img, tex_x, tex_y);

				// 🔥 ПРОЗРАЧНОСТЬ
				if ((color & 0x00FFFFFF) != 0)
					put_pixel(&g->screen, screen_x, screen_y, color);
			}
			x++;
		}
		y++;
	}
}
