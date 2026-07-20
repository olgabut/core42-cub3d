#include "renderer.h"

int	is_wall(t_graphics *g, int x, int y)
{
	char	cell;

	if (y < 0 || y >= (int)g->scene->map.size_y
		|| x < 0 || x >= (int)g->scene->map.size_x)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(g->scene->map.map[y]))
		return (1);
	cell = g->scene->map.map[y][x];
	if (cell == '1')
		return (1);
	#ifdef BONUS
	if (cell == '2' && g->door_state[y][x] == 0)
		return (1);
	if (cell == '3')
		return (0);
	#endif
	return (0);
}
