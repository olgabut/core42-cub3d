/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_strtrim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obutolin <obutolin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:08:42 by obutolin          #+#    #+#             */
/*   Updated: 2026/05/29 12:11:06 by obutolin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_changed(char *str)
{
	size_t	len;
	size_t	i;

	while (*str == ' ')
		str++;
	len = ft_strlen(str);
	if (len < 1)
		return (str);
	i = 0;
	if (str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
		i = 1;
	}
	while ((len > (i + 1)) && str[len - i - 1] == ' ')
		i++;
	str[len - i] = '\0';
	return (str);
}
