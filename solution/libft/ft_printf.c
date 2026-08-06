/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:56:25 by dprikhod          #+#    #+#             */
/*   Updated: 2026/07/23 10:58:08 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_var_handle(const char *format, va_list args, int i, int fd)
{
	int	temp;

	temp = 1;
	if (format[i + 1] == 'c')
		ft_putchar_fd(va_arg(args, int), fd);
	else if (format[i + 1] == 's')
		temp = s_handle(va_arg(args, char *), fd);
	else if (format[i + 1] == 'p')
		temp = p_handle(va_arg(args, void *), fd);
	else if (format[i + 1] == 'd' || format[i + 1] == 'i')
		temp = i_handle(va_arg(args, int), fd);
	else if (format[i + 1] == 'u')
		temp = u_handle(va_arg(args, unsigned int), fd);
	else if (format[i + 1] == 'x')
		temp = x_handle((unsigned long)va_arg(args, unsigned int),
				"0123456789abcdef", fd);
	else if (format[i + 1] == 'X')
		temp = x_handle((unsigned long)va_arg(args, unsigned int),
				"0123456789ABCDEF", fd);
	else
		ft_putchar_fd('%', fd);
	return (temp);
}

/*
c - char
s - string
p - pointer
d - decimal
i - integer in base 10
u - unsigned decimal
x - lowercase hexidecimal
X - uppercase hexidecimal
% - percentage sign
*/
static int	helper(const char *format, va_list args, int *i, int fd)
{
	int	count;

	count = 0;
	if (format[*i] == '%')
	{
		if (format[*i + 1])
			count += ft_var_handle(format, args, *i, fd);
		else
			return (-1);
		(*i)++;
	}
	else
	{
		ft_putchar_fd(format[*i], fd);
		count++;
	}
	return (count);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		ret;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		ret = helper(format, args, &i, fd);
		if (ret == -1)
			return (ret);
		count += ret;
		i++;
	}
	va_end(args);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		ret;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		ret = helper(format, args, &i, STDOUT_FILENO);
		if (ret == -1)
			return (ret);
		count += ret;
		i++;
	}
	va_end(args);
	return (count);
}
