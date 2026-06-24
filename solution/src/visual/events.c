#include "renderer.h"

#ifdef BONUS
int	handle_mouse(int x, int y, t_graphics *graphics)
{
	int	dx;
	int	center;

	(void)y;
	center = WINDOW_WIDTH / 2;
	if (x == center)
		return (0);
	dx = x - center;
	graphics->player.angle += (double)dx * 0.003;
	mlx_mouse_move(graphics->window, center, WINDOW_HEIGHT / 2);
	return (0);
}

static void	toggle_door(t_graphics *g)
{
	int		map_x;
	int		map_y;
	double	check_x;
	double	check_y;

	check_x = g->player.x + cos(g->player.angle) * 64;
	check_y = g->player.y + sin(g->player.angle) * 64;
	map_x = (int)(check_x / 64);
	map_y = (int)(check_y / 64);
	if (map_x < 0 || map_y < 0 || map_x >= (int)g->scene->map.size_x || map_y >= (int)g->scene->map.size_y)
		return ;
	if (g->scene->map.map[map_y][map_x] == '2')
		g->door_state[map_y][map_x] ^= 1;
}
#endif

int	handle_key_press(int keycode, t_graphics *graphics)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(graphics->mlx, graphics->window);
		exit(0);
	}
	#ifdef BONUS
	if (keycode == KEY_F)
		toggle_door(graphics);
	#endif
	if (keycode >= 0 && keycode < 70000)
		graphics->keys_pressed[keycode] = 1;
	return (0);
}

int	handle_key_release(int keycode, t_graphics *graphics)
{
	if (keycode >= 0 && keycode < 70000)
		graphics->keys_pressed[keycode] = 0;
	return (0);
}

int	handle_close(t_graphics *graphics)
{
	mlx_destroy_window(graphics->mlx, graphics->window);
	exit(0);
	return (0);
}

#ifdef BONUS
static int	is_wall_at(t_graphics *g, double x, double y, double margin)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)((x + margin) / 64);
	map_y = (int)((y + margin) / 64);
	if (map_x < 0 || map_y < 0 || map_x >= (int)g->scene->map.size_x || map_y >= (int)g->scene->map.size_y)
		return (1);
	cell = g->scene->map.map[map_y][map_x];
	if (cell == '1' || (cell == '2' && g->door_state[map_y][map_x] == 0))
		return (1);
	map_x = (int)((x - margin) / 64);
	map_y = (int)((y - margin) / 64);
	if (map_x < 0 || map_y < 0
		|| map_x >= (int)g->scene->map.size_x
		|| map_y >= (int)g->scene->map.size_y)
		return (1);
	cell = g->scene->map.map[map_y][map_x];
	if (cell == '1' || (cell == '2' && g->door_state[map_y][map_x] == 0))
		return (1);
	map_x = (int)((x + margin) / 64);
	map_y = (int)((y - margin) / 64);
	if (map_x < 0 || map_y < 0
		|| map_x >= (int)g->scene->map.size_x
		|| map_y >= (int)g->scene->map.size_y)
		return (1);
	cell = g->scene->map.map[map_y][map_x];
	if (cell == '1' || (cell == '2' && g->door_state[map_y][map_x] == 0))
		return (1);
	map_x = (int)((x - margin) / 64);
	map_y = (int)((y + margin) / 64);
	if (map_x < 0 || map_y < 0
		|| map_x >= (int)g->scene->map.size_x
		|| map_y >= (int)g->scene->map.size_y)
		return (1);
	cell = g->scene->map.map[map_y][map_x];
	if (cell == '1' || (cell == '2' && g->door_state[map_y][map_x] == 0))
		return (1);
	return (0);
}
#endif

/* Updates player position and rotation based on key presses */
static void	update_player(t_graphics *graphics)
{
	double	move_x;
	double	move_y;
	double	new_x;
	double	new_y;
	#ifdef BONUS
	double	margin;

	margin = 8.0;
	#endif
	move_x = 0;
	move_y = 0;
	if (graphics->keys_pressed[KEY_W])
	{
		move_x += cos(graphics->player.angle) * graphics->move_speed;
		move_y += sin(graphics->player.angle) * graphics->move_speed;
	}
	if (graphics->keys_pressed[KEY_S])
	{
		move_x -= cos(graphics->player.angle) * graphics->move_speed;
		move_y -= sin(graphics->player.angle) * graphics->move_speed;
	}
	if (graphics->keys_pressed[KEY_A])
	{
		move_x -= cos(graphics->player.angle + PI / 2) * graphics->move_speed;
		move_y -= sin(graphics->player.angle + PI / 2) * graphics->move_speed;
	}
	if (graphics->keys_pressed[KEY_D])
	{
		move_x += cos(graphics->player.angle + PI / 2) * graphics->move_speed;
		move_y += sin(graphics->player.angle + PI / 2) * graphics->move_speed;
	}
	new_x = graphics->player.x + move_x;
	new_y = graphics->player.y + move_y;
	#ifdef BONUS
	if (!is_wall_at(graphics, new_x, graphics->player.y, margin))
		graphics->player.x = new_x;
	if (!is_wall_at(graphics, graphics->player.x, new_y, margin))
		graphics->player.y = new_y;
	#else
	{
		int	map_x;
		int	map_y;

		map_x = (int)(new_x / 64);
		map_y = (int)(new_y / 64);
		if (map_x >= 0 && map_x < (int)graphics->scene->map.size_x &&
			map_y >= 0 && map_y < (int)graphics->scene->map.size_y &&
			graphics->scene->map.map[map_y][map_x] != '1')
		{
			graphics->player.x = new_x;
			graphics->player.y = new_y;
		}
	}
	#endif
	if (graphics->keys_pressed[KEY_LEFT])
		graphics->player.angle -= graphics->rotate_speed;
	if (graphics->keys_pressed[KEY_RIGHT])
		graphics->player.angle += graphics->rotate_speed;
}

/* Main game loop */
int	game_loop(t_graphics *graphics)
{
	update_player(graphics);
	render_frame(graphics);
	return (0);
}