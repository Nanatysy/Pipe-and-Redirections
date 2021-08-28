#ifndef PIPEX_PIPEX_H
#define PIPEX_PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct	s_all
{
	char	***arg;
	int		my_pipe[2];
	int		tmp_fd;
	int		input_fd;
	int		output_fd;
	pid_t	pid[2];
}				t_all;

void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);

#endif //PIPEX_PIPEX_H
