
#include "libft.h"

static char	*fetch_line(int fd, char **stash)
{
	ssize_t	check;
	char	*buf;
	char	*tmp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(*stash), NULL);
	check = 1;
	while (check > 0)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
			return (free(*stash), free(buf), NULL);
		buf[check] = '\0';
		if (!(*stash))
			*stash = ft_strdup("");
		tmp = ft_strjoin(*stash, buf);
		free(*stash);
		*stash = tmp;
		if (!*stash || ft_strchr(*stash, '\n'))
			break ;
	}
	free(buf);
	return (*stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*tmp;
	ssize_t		len;

	stash = fetch_line(fd, &stash);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_substr(stash, 0, len);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	tmp = ft_substr(stash, len, ft_strlen(stash) - len);
	free(stash);
	stash = tmp;
	return (line);
}
