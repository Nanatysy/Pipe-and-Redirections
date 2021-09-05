#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*res;
	unsigned char	*tmp;
	size_t			i;

	res = (void *)malloc(count * size);
	if (!res)
		return (NULL);
	i = 0;
	tmp = res;
	while (i < count * size)
	{
		tmp[i] = 0;
		i++;
	}
	return (res);
}
