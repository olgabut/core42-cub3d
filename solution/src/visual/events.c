#include "renderer.h"

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
