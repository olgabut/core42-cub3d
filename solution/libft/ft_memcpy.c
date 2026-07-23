/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:03:11 by vivantso          #+#    #+#             */
/*   Updated: 2026/07/23 10:43:12 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destin;
	const unsigned char	*source;

	if (!dest && !src && n > 0)
		return (NULL);
	if (!dest && !src && n == 0)
		return (dest);
	destin = (unsigned char *)dest;
	source = (const unsigned char *)src;
	while (n--)
		*destin++ = *source++;
	return (dest);
}
