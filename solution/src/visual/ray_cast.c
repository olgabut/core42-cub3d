#include "renderer.h"

/* Ray casting implementation using grid-based DDA algorithm */

static void	render_wall_column(t_image *img, t_shape shape,
	int tex_x, t_vec v)
{
	int		tex_y;
	double	o;
	double	cur;
	char	*dst;

	o = shape.img->height / (double)shape.height;
	cur = o * (v.y - shape.y);
	if (cur < 0)
		cur = 0;
	dst = img->data + (v.y * img->size_line + shape.x * (img->bpp / 8));
	while (v.y < shape.y + shape.height && v.y < WINDOW_HEIGHT)
	{
		tex_y = (int)cur;
		if (tex_y >= 0 && tex_y < shape.img->height)
			*(unsigned int *)dst = *(unsigned int *)(shape.img->data
					+ (tex_y * shape.img->size_line + tex_x
						* (shape.img->bpp / 8)));
		else
			*(unsigned int *)dst = 0;
		dst += img->size_line;
		cur += o;
		v.y++;
	}
}

static void	set_img_strip(t_image *img, t_shape shape, double offset)
{
	t_vec		v;
	int			tex_x;

	if (!shape.img || shape.img->width <= 0 || shape.height <= 0
		|| shape.height < 1 || shape.x < 0 || shape.x >= WINDOW_WIDTH)
		return ;
	v.y = (int)fmax(0, shape.y);
	if (v.y >= WINDOW_HEIGHT)
		return ;
	tex_x = (int)((shape.img->width - 1) * offset);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= shape.img->width)
		tex_x = shape.img->width - 1;
	render_wall_column(img, shape, tex_x, v);
}

static void	cast_forward(t_ray_grid *ray, t_ray_grid step)
{
	if (ray->ln_cos < ray->ln_sin)
	{
		ray->st_cos_x += step.st_cos_x;
		ray->st_cos_y += step.st_cos_y;
		ray->ln_cos += step.ln_cos;
	}
	else
	{
		ray->st_sin_x += step.st_sin_x;
		ray->st_sin_y += step.st_sin_y;
		ray->ln_sin += step.ln_sin;
	}
}

static void	do_ray(t_graphics *g, t_trace *tr)
{
	tr->pos = get_collide_pos(*tr);
	if (is_wall(g, tr->pos.x, tr->pos.y))
	{
		setup_line(g, tr);
		#ifdef BONUS
		g->wall_dist[tr->line.x] = tr->len;
		#endif
		if (tr->line.img)
			set_img_strip(&g->screen, tr->line, tr->offset);
		tr->i = 200;
		return ;
	}
	if (tr->i < 200 && tr->pos.x >= 0
		&& tr->pos.x < (int)g->scene->map.size_x && tr->pos.y >= 0
		&& tr->pos.y < (int)g->scene->map.size_y)
	{
		cast_forward(&tr->ray, tr->step);
		tr->i++;
	}
	else if (tr->i < 200)
	{
		setup_line(g, tr);
		if (tr->line.img)
			set_img_strip(&g->screen, tr->line, tr->offset);
		tr->i = 200;
	}
}

void	ray_cast(t_graphics *g)
{
	t_trace	trace;
	double	fov;
	double	player_grid_x;
	double	player_grid_y;

	draw_floor_ceiling(g);
	fov = (double)WINDOW_HEIGHT / (double)WINDOW_WIDTH;
	player_grid_x = g->player.x / 64.0;
	player_grid_y = g->player.y / 64.0;
	trace.line.width = 1;
	trace.line.x = -1;
	while (++trace.line.x < WINDOW_WIDTH)
	{
		trace.newa = atan2((trace.line.x / (double)WINDOW_WIDTH) - 0.5, fov);
		trace.rot = make_rot(g->player.angle + trace.newa);
		trace.ref_x = player_grid_x;
		trace.ref_y = player_grid_y;
		trace.ray = get_init_ray(&trace.rot, trace.ref_x, trace.ref_y);
		trace.step = get_init_ray(&trace.rot, 0, 0);
		trace.i = 0;
		while (trace.i < 200)
			do_ray(g, &trace);
	}
}
