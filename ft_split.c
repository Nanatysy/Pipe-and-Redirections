#include "pipex.h"

int	ft_count(char *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	word = 0;
	count = 1;
	if (s[i] == '\0' || s[ft_strlen(s) - 1] == c)
		count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			word = 1;
		if (s[i] == c && word)
		{
			count++;
			word = 0;
		}
		i++;
	}
	return (count);
}

int	ft_find_word(char *s, char c, int start)
{
	while (s[start] != c && s[start] != '\0')
		start++;
	while (s[start] == c && s[start] != '\0')
		start++;
	return (start);
}

void	ft_put_null(char **s, char c)
{
	char	*tmp;
	int		i;

	tmp = *s;
	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == c)
			tmp[i] = '\0';
		i++;
	}
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		count;
	int		i;
	int		word;

	count = ft_count((char *)s, c);
	res = ft_calloc(count + 2, sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = ft_strdup(s);
	if (!res[0])
		return (NULL);
	i = 1;
	word = 0;
	while (res[0][word] == c && res[0][word] != '\0')
		word++;
	while (i <= count)
	{
		res[i] = &res[0][word];
		word = ft_find_word(res[0], c, word);
		i++;
	}
	ft_put_null(&res[0], c);
	return (res);
}
