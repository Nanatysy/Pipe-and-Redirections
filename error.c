#include "pipex.h"

int	error(int flag, char *arg, t_all *all)
{
	if (flag == FD_ERROR)
	{
		write(2, "permission denied: ", ft_strlen("permission denied: "));
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	}
	else if (flag == SYSCALL_ERROR)
		write(2, "error\n", ft_strlen("Fork error\n"));
	else if (flag == EXECVE_ERROR)
	{
		write(2, "command not found: ", ft_strlen("command not found: "));
		write(2, arg, ft_strlen(arg));
		write(2, "\n", 1);
	}
	else if (flag == ARG_ERROR)
		write(2, "wrong number of arguments\n",
			  ft_strlen("wrong number of arguments\n"));
	if (flag != FD_ERROR)
		free_all_and_close(all);
	return (1);
}

void	my_dup(t_all *all)
{
	dup2(all->my_pipe[0], 0);
	close(all->my_pipe[0]);
	close(all->my_pipe[1]);
}
