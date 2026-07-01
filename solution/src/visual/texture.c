#include "renderer.h"

/* Wall collision detection and texture mapping */

t_vec	get_collide_pos(t_trace tr)
{
	t_vec	pos;

	if (tr.ray.ln_cos > tr.ray.ln_sin)
	{
		pos.x = floor(tr.ref_x + tr.ray.st_sin_x);
		pos.y = floor(tr.ref_y + tr.ray.st_sin_y + tr.rot.sin / 2);
	}
	else
	{
		pos.x = floor(tr.ref_x + tr.ray.st_cos_x + tr.rot.cos / 2);
		pos.y = floor(tr.ref_y + tr.ray.st_cos_y);
	}
	return (pos);
}

char	get_side(t_trace trace)
{
	if (trace.ray.ln_cos < trace.ray.ln_sin)
	{
		if (trace.rot.cos > 0)
			return ('E');
		return ('W');
	}
	if (trace.rot.sin > 0)
		return ('S');
	return ('N');
}

t_image	*get_texture(t_graphics *g, char side)
{
	if (side == 'N')
		return (&(g->north));
	if (side == 'S')
		return (&(g->south));
	if (side == 'W')
		return (&(g->west));
	return (&(g->east));
}

void	setup_line(t_graphics *g, t_trace *tr)
{
	tr->side = get_side(*tr);
	tr->len = fmin(tr->ray.ln_cos, tr->ray.ln_sin);
	tr->line.height = (int)(WINDOW_HEIGHT / (tr->len * cos(tr->newa)));
	if (tr->line.height < 1)
		tr->line.height = 1;
	tr->line.y = (WINDOW_HEIGHT - tr->line.height) / 2;
	tr->line.img = get_texture(g, tr->side);
	tr->offset = tex_offset(*tr);
}

int	is_wall(t_graphics *g, int x, int y)
{
	char	cell;

	if (y < 0 || y >= (int)g->scene->map.size_y ||
		x < 0 || x >= (int)g->scene->map.size_x)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(g->scene->map.map[y]))
		return (1);
	cell = g->scene->map.map[y][x];
	if (cell == '1')
		return (1);
	#ifdef BONUS
	if (cell == '2' && g->door_state[y][x] == 0)
		return (1);
	#endif
	return (0);
}

double	tex_offset(t_trace trace)
{
	double	offset;

	if (trace.ray.ln_cos < trace.ray.ln_sin)
	{
		offset = trace.ref_x + trace.ref_y + trace.ray.st_cos_x
			+ trace.ray.st_cos_y;
		offset -= (int)offset;
		if (trace.rot.cos < 0)
			offset = 1 - offset;
	}
	else
	{
		offset = trace.ref_x + trace.ref_y + trace.ray.st_sin_x
			+ trace.ray.st_sin_y;
		offset -= (int)offset;
		if (trace.rot.sin > 0)
			offset = 1 - offset;
	}
	return (offset);
}

