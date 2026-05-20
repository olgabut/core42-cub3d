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
