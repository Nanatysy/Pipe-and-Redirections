#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define FD_ERROR 1
# define SYSCALL_ERROR 2
# define EXECVE_ERROR 3
# define ARG_ERROR 4

typedef struct s_all
{
	char	***arg;
	int		my_pipe[2];
	int		input_fd;
	int		output_fd;
	pid_t	pid[2];
}				t_all;

void	free_all_and_close(t_all *all);
void	init_all(t_all *all, char **argv);
void	my_dup(t_all *all);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2, int flag);
char	*find_path(char *arg, char **env);
char	*find_path_extra(char **path_tmp, char *arg);
int		ft_strlen(char *str);
int		error(int flag, char *arg, t_all *all);
int		chech_arg(const char *arg);
int		ft_strcmp(const char *src, const char *ref);
int		fd_error(t_all *all, char **argv);

#endif //PIPEX_PIPEX_H
