/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 10:47:02 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/25 09:28:04 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H


int		check_argument(int arg_count);
int		check_file_extantion(char *fname);
void	print_no_argument(void);
void	print_too_many_arguments(void);
void	print_invalid_file_extension(void);
void	print_file_not_found(void);

#endif