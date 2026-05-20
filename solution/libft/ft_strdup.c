#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
