/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:51:58 by dprikhod          #+#    #+#             */
/*   Updated: 2026/07/23 11:11:18 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	s_handle(char *s, int fd)
{
	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}

int	u_handle(unsigned int u, int fd)
{
	char	buf[12];
	int		i;
	int		temp;

	i = 0;
	if (u == 0)
		buf[i++] = '0';
	while (u > 0)
	{
		buf[i++] = (u % 10) + '0';
		u /= 10;
	}
	temp = i;
	while (i > 0)
		write(fd, &buf[--i], 1);
	return (temp);
}

int	i_handle(int n, int fd)
{
	unsigned int	num;
	int				sign;
	int				res;

	sign = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		num = -(unsigned int)n;
		sign = 1;
	}
	else
		num = (unsigned int)n;
	res = u_handle(num, fd);
	return (res + sign);
}

int	x_handle(unsigned long x, char *base, int fd)
{
	char	hex[15];
	int		i;
	int		temp;

	i = 0;
	if (x == 0)
		hex[i++] = '0';
	while (x > 0)
	{
		hex[i++] = base[x % 16];
		x /= 16;
	}
	temp = i;
	while (i > 0)
		write(fd, &hex[--i], 1);
	return (temp);
}

int	p_handle(void *p, int fd)
{
	unsigned long	addr;
	int				temp;

	addr = (unsigned long)p;
	if (addr == 0)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	ft_putstr_fd("0x", fd);
	temp = 2;
	temp += x_handle(addr, "0123456789abcdef", fd);
	return (temp);
}
