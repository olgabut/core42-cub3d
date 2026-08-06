/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/23 10:43:18 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*destin;
	const char	*source;

	source = (const char *)src;
	destin = (char *)dest;
	if (destin == source || n == 0)
		return (dest);
	if (destin < source)
	{
		while (n--)
			*destin++ = *source++;
	}
	else
	{
		destin += n;
		source += n;
		while (n--)
			*--destin = *--source;
	}
	return (dest);
}
