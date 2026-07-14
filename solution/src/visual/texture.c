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

static char	get_side(t_trace trace)
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

static t_image	*get_texture(t_graphics *g, char side)
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
	#ifdef BONUS
	t_vec hit = get_collide_pos(*tr);
	int map_x = (int)hit.x;
	int map_y = (int)hit.y;
	if (g->scene->map.map[map_y][map_x] == '2')
		tr->line.img = &(g->door);
	else if (g->scene->map.map[map_y][map_x] == '3')
		tr->line.img = &(g->fire);
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
	#else
	tr->line.img = get_texture(g, tr->side);
	#endif
	tr->offset = tex_offset(*tr);
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
