#include "libft.h"

static size_t	ft_substr_len(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (0);
	if (len > s_len - start)
		return (s_len - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	sub_len;

	if (!s)
		return (NULL);
	sub_len = ft_substr_len(s, start, len);
	sub = (char *)malloc(sub_len + 1);
	if (!sub)
		return (NULL);
	if (start < ft_strlen(s))
		ft_strlcpy(sub, (char *)&s[start], sub_len + 1);
	else
		sub[0] = '\0';
	return (sub);
}
