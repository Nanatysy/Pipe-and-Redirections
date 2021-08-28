#include "pipex.h"

int	error(int flag, char *arg)
{
	if (flag == FD_ERROR)
	{
		write(2, "permission denied: ", ft_strlen("permission denied: "));
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
		// free
	}

	return (1);
}