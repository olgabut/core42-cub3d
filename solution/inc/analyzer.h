/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:38:57 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/03 21:53:25 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYZER_H
# define ANALYZER_H

#include "cub3d.h"

void	analyse_texture(t_scene *scene, char *line, int line_num);
void	analyse_color(t_scene *scene, char *line, int line_num);
void	analyse_map_line(t_scene *scene, char *line, int line_num);

#endif