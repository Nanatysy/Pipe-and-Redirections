#include "pipex.h"

void	free_all_and_close(t_all *all)
{
	if (!all)
		return ;
	if (all->arg)
	{
		if (all->arg[0])
		{
			free(all->arg[0][0]);
			free(all->arg[0]);
		}
		if (all->arg[1])
		{
			free(all->arg[1][0]);
			free(all->arg[1]);
		}
		free(all->arg);
	}
	close(all->input_fd);
	close(all->output_fd);
	close(all->my_pipe[0]);
	close(all->my_pipe[1]);
}

void	init_all(t_all *all, char **argv)
{
	all->arg = malloc(sizeof(char **) * 2);
	if (!all->arg)
		error(SYSCALL_ERROR, NULL, all);
	all->arg[0] = ft_split(argv[2], ' ');
	all->arg[1] = ft_split(argv[3], ' ');
	if (!all->arg[0] || !all->arg[1])
		error(SYSCALL_ERROR, NULL, all);
}

int	my_fork(t_all *all, int flag, char **env)
{
	int		i;
	char	*tmp;

	all->pid[flag] = fork();
	if (all->pid[flag] == 0)
	{
		dup2(all->my_pipe[1], 1);
		close(all->my_pipe[0]);
		close(all->my_pipe[1]);
		tmp = find_path(all->arg[flag][0], env);
		i = execve(tmp, &all->arg[flag][1], env);
		free(tmp);
		if (i == -1)
			error(EXECVE_ERROR, all->arg[flag][1], all);
		exit(0);
	}
	else if (all->pid[flag] < 0)
		error(SYSCALL_ERROR, NULL, all);
	else
	{
		if (flag == 0)
			my_dup(all);
	}
	return (0);
}

int	fd_error(t_all *all, char **argv)
{
	if (all->input_fd == -1)
		error(FD_ERROR, argv[1], all);
	if (all->output_fd == -1)
		error(FD_ERROR, argv[4], all);
	free_all_and_close(all);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_all	all;

	if (argc != 5)
		return (error(ARG_ERROR, NULL, NULL));
	init_all(&all, argv);
	all.input_fd = open(argv[1], O_RDONLY);
	all.output_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND,
			 0666);
	if (all.input_fd == -1 || all.output_fd == -1)
		return (fd_error(&all, argv));
	pipe(all.my_pipe);
	dup2(all.input_fd, 0);
	close (all.input_fd);
	my_fork(&all, 0, env);
	dup2(all.output_fd, all.my_pipe[1]);
	close(all.output_fd);
	my_fork(&all, 1, env);
	waitpid(all.pid[0], NULL, 0);
	waitpid(all.pid[1], NULL, 0);
	free_all_and_close(&all);
	return (0);
}
