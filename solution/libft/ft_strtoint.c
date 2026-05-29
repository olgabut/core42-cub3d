/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:44:40 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/29 09:51:25 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

// INT_MAX =  2147483647
// INT_MIN = -2147483648
int	get_unsigned_num(long long *num, char *str, int sign)
{
	long int	long_num;

	long_num = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		long_num = (long_num * 10) + (*str - '0');
		str++;
		if (long_num * sign < INT_MIN || long_num * sign > INT_MAX)
			return (0);
	}
	*num = long_num;
	return (1);
}

/*
	The ft_strtoint() function converts string (str) to integer number (*ptr_num)
	Parameters:
		int *ptr_num: pointer to integer for number.
		char *str: string
	Return:
		1 - correct number
		0 - error
*/
int	ft_strtoint(int *ptr_num, char *str)
{
	long long	long_num;
	int			minus;

	if (!str || !ptr_num)
		return (0);
	minus = 1;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	if (!*str)
		return (0);
	if (!get_unsigned_num(&long_num, str, minus))
		return (0);
	long_num *= minus;
	if (long_num < INT_MIN || long_num > INT_MAX)
		return (0);
	*ptr_num = (int)long_num;
	return (1);
}
