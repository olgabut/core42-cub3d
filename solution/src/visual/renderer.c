#include "renderer.h"

void	render_frame(t_graphics *g)
{
	ray_cast(g);
	#ifdef BONUS
	draw_fire(g);
	draw_minimap(g);
	#endif
	mlx_put_image_to_window(g->mlx, g->window, g->screen.ptr, 0, 0);
}

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
