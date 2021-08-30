#ifndef PIPEX_PIPEX_H
#define PIPEX_PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define FD_ERROR 1
#define SYSCALL_ERROR 2
#define EXECVE_ERROR 3
#define ARG_ERROR 4

typedef struct	s_all
{
	char	***arg;
	int		my_pipe[2];
	int		tmp_fd;
	int		input_fd;
	int		output_fd;
	pid_t	pid[2];
}				t_all;

void	free_all_and_close(t_all *all);
void	init_all(t_all *all, char **argv);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
int		error(int flag, char *arg, t_all *all);

#endif //PIPEX_PIPEX_H
