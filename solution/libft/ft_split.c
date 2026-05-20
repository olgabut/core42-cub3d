#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	in_word;

	count = 0;
	in_word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static void	free_result(char **result, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

static char	*allocate_word(char const *start, \
size_t len, char **result, size_t i)
{
	char	*word;

	word = (char *)malloc(len + 1);
	if (!word)
	{
		free_result(result, i);
		return (NULL);
	}
	ft_memcpy(word, start, len);
	word[len] = '\0';
	return (word);
}

static char	**make_result(char **result, char const *s, char c)
{
	size_t		i;
	size_t		word_len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		word_len = 0;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		if (word_len)
		{
			result[i] = allocate_word(s, word_len, result, i);
			if (!result[i])
				return (NULL);
			i++;
		}
		s += word_len;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result = make_result(result, s, c);
	if (!result)
		return (NULL);
	return (result);
}
