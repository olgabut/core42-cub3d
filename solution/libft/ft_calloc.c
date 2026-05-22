#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}
