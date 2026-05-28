/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 09:38:57 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/28 14:39:54 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANALYZER_H
# define ANALYZER_H

#include "cub3d.h"

void	analyse_texture_info(t_scene *scene, char *line, int line_num);
void	analyse_color_info(t_scene *scene, char *line, int line_num,
	t_memory_info **memory);

#endif