/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/21 14:18:57 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

/* Ray initialization and rotation utilities */

t_rot	make_rot(double angle)
{
	t_rot	rot;

	rot.angle = angle;
	rot.cos = cos(rot.angle);
	rot.sin = sin(rot.angle);
	return (rot);
}

t_ray_grid	get_init_ray(t_rot *rot, double x, double y)
{
	t_ray_grid	ray;

	if (rot->cos > 0)
		ray.st_cos_x = floor(x + 1) - x;
	else
		ray.st_cos_x = ceil(x - 1) - x;
	ray.st_cos_y = ray.st_cos_x * (rot->sin / rot->cos);
	ray.ln_cos = sqrt(pow(ray.st_cos_x, 2) + pow(ray.st_cos_y, 2));
	if (rot->sin > 0)
		ray.st_sin_y = floor(y + 1) - y;
	else
		ray.st_sin_y = ceil(y - 1) - y;
	ray.st_sin_x = ray.st_sin_y * (rot->cos / rot->sin);
	ray.ln_sin = sqrt(pow(ray.st_sin_x, 2) + pow(ray.st_sin_y, 2));
	return (ray);
}
