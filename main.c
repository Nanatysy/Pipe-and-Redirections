#include "pipex.h"

int	my_fork(t_all *all, int flag, char **env)
{
	int	i;

	all->pid[flag] = fork();
	if (all->pid[flag] == 0)
	{
		if (flag == 0)
		{
			dup2(all->my_pipe[1], 1);
			close(all->my_pipe[0]);
			close(all->my_pipe[1]);
		}
		i = execve(all->arg[flag][0], &all->arg[flag][1], env);
		if (i == -1)
		{
			write(2, "no such file or directory: ", ft_strlen("no such file "
															  "or directory: "));
			write(2, all->arg[flag][0], ft_strlen(all->arg[flag][0]));
			write(2, "\n", 1);
		}
		exit(0);
	}
	else if (all->pid[flag] < 0)
	{
		write(2, "Fork error\n", ft_strlen("Fork error\n"));
		exit(0);
	}
	else
	{
		if (flag == 0)
		{
			dup2(all->my_pipe[0], 0);
			close(all->my_pipe[0]);
			close(all->my_pipe[1]);
		}
	}
	return (0);
}


int	main(int argc, char **argv, char **env)
{
	t_all	all;
	int		status;

	if (argc != 5)
		return (error(ARG_ERROR, NULL));
	all.input_fd = open(argv[1], O_RDONLY);
	if (all.input_fd == -1)
		return (error(FD_ERROR, argv[1]));
	all.output_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0666);
	if (all.output_fd == -1)
		return (error(FD_ERROR, argv[4]));

	// malloc part
	all.arg = malloc(sizeof(char **) * 2);
	if (!all.arg)
		return (2);
	all.arg[0] = ft_split(argv[2], ' ');
	all.arg[1] = ft_split(argv[3], ' ');
	all.tmp_fd = dup(0);

	pipe(all.my_pipe);
	dup2(all.input_fd, 0);
	close (all.input_fd);
	my_fork(&all, 0, env);
	dup2(all.output_fd, 1);
	close(all.output_fd);
	my_fork(&all, 1, env);
	waitpid(all.pid[0], &status, 0);
	waitpid(all.pid[1], &status, 0);
	dup2(all.tmp_fd, 0);
	close(all.tmp_fd);

	// free part

	free(all.arg[0][0]);
	free(all.arg[0]);
	free(all.arg[1][0]);
	free(all.arg[1]);
	free(all.arg);

	return (0);
}