/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 09:50:14 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/22 11:00:38 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "cub3d.h"

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720
# define PI				3.14159265359
# define FOV			60

# ifdef __APPLE__
// macOS key codes
#  define KEY_W			13
#  define KEY_A			0
#  define KEY_S			1
#  define KEY_D			2
#  define KEY_UP		126
#  define KEY_DOWN		125
#  define KEY_LEFT		123
#  define KEY_RIGHT		124
#  define KEY_ESC		53
#  define KEY_F			3
# else
// linux key codes
#  define KEY_W			119
#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_UP			65362
#  define KEY_DOWN		65364
#  define KEY_LEFT		65361
#  define KEY_RIGHT		65363
#  define KEY_ESC		65307
#  define KEY_F			102
# endif

/* minimap params */
# define MM_SCALE		8
# define MM_X			14
# define MM_Y			14
# define MM_VIEW		160
# define MM_PADDING		6

typedef struct s_image
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_rot
{
	double	angle;
	double	cos;
	double	sin;
}	t_rot;

typedef struct s_ray_grid
{
	double	st_cos_x;
	double	st_cos_y;
	double	st_sin_x;
	double	st_sin_y;
	double	ln_cos;
	double	ln_sin;
}	t_ray_grid;

typedef struct s_shape
{
	int		x;
	int		y;
	int		width;
	int		height;
	t_image	*img;
}	t_shape;

typedef struct s_trace
{
	t_shape		line;
	t_rot		rot;
	t_ray_grid	ray;
	t_ray_grid	step;
	t_vec		pos;
	double		newa;
	double		ref_x;
	double		ref_y;
	int			i;
	char		side;
	double		len;
	double		offset;
}	t_trace;

typedef struct s_ray
{
	double	distance;
	double	angle;
	int		is_vertical;
	int		wall_side;
	char	*texture_ptr;
	int		texture_x;
}	t_ray;

typedef struct s_graphics
{
	void		*mlx;
	void		*window;
	t_image		screen;
	t_image		north;
	t_image		south;
	t_image		west;
	t_image		east;
	t_player	player;
	t_scene		*scene;
	int			moved;
	int			rotated;
	double		move_speed;
	double		rotate_speed;
	char		keys_pressed[70000];
	t_image		door;
	char		door_state[64][64]; // 0 = closed, 1 = opened
	t_image		fire_frames[5];
	int			fire_frame;
	long		fire_last_time;
	double		wall_dist[WINDOW_WIDTH];
}	t_graphics;

// draw_utils.c
void		put_pixel(t_image *image, int x, int y, int color);
void		draw_floor_ceiling(t_graphics *g);
// event_game_loop.c
double		move_player_x(t_graphics *graphics);
double		move_player_y(t_graphics *graphics);
int			game_loop(t_graphics *graphics);
// events.c
int			handle_key_press(int keycode, t_graphics *graphics);
int			handle_key_release(int keycode, t_graphics *graphics);
int			handle_close(t_graphics *graphics);
// graphics_init.c
int			load_texture(t_graphics *graphics, t_image *img, const char *path);
int			init_graphics(t_graphics *graphics, t_scene *scene);
// free_graphics.c
void		free_graphics(t_graphics *graphics);
// ray_cast.c
void		ray_cast(t_graphics *g);
// get_pixel.c
int			get_pixel(t_image *img, int x, int y);
// ray2.c
t_rot		make_rot(double angle);
t_ray_grid	get_init_ray(t_rot *rot, double x, double y);
// renderer.c
void		render_frame(t_graphics *g);
double		normalize_angle(double angle);
// texture.c
t_vec		get_collide_pos(t_trace tr);
void		setup_line(t_graphics *g, t_trace *tr);
double		tex_offset(t_trace trace);
t_image		*get_texture(t_graphics *g, char side);
// is_wall.c
int			is_wall(t_graphics *g, int x, int y);

// BONUS
// event_bonus.c
int			handle_mouse(int x, int y, t_graphics *graphics);
void		toggle_door(t_graphics *g);
// minimap_bonus.c
void		draw_minimap(t_graphics *g);
// minimap2_bonus.c
void		mm_draw_bg(t_image *s);
void		mm_draw_arrow(t_image *s, int cx, int cy, double angle);
// is_wall_at_bonus.c
int			is_wall_at(t_graphics *g, double x, double y, double margin);
void		update_player_bonus(t_graphics *graphics);
// fire_init_bonus.c
int			init_fire_texture(t_graphics *graphics);
void		free_fire_img(t_graphics *graphics);
void		draw_fire(t_graphics *g);
// fire_draw_bonus.c
void		update_fire(t_graphics *g);
void		draw_sprite_fire(t_graphics *g, t_shape s, double sprite_dist);
// texture_bonus.c
void		setup_line_bonus(t_graphics *g, t_trace *tr);
#endif