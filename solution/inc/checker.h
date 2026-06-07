/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:47:02 by obutolin          #+#    #+#             */
/*   Updated: 2026/06/07 15:47:14 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H


int		check_argument(int arg_count);
int		check_file_extantion(char *fname);
int		check_data_from_file(t_scene *scene);
int		check_map_from_file(t_scene *scene);
void	print_no_argument(void);
void	print_too_many_arguments(void);
void	print_invalid_file_extension(void);
void	print_file_not_found(void);
void	print_no_texture(char cardinal_direction);

#endif