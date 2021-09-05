#include "pipex.h"

int	chech_arg(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *src, const char *ref)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && ref[i] != '\0' && src[i] == ref[i])
		i++;
	if (ref[i] == '\0')
		return (1);
	return (0);
}

char	*find_path_extra(char **path_tmp, char *arg)
{
	int		i;
	char	*tmp;

	i = 1;
	while (path_tmp[i] != NULL)
	{
		tmp = ft_strjoin(path_tmp[i], "/", 0);
		tmp = ft_strjoin(tmp, arg, 1);
		if (access(tmp, F_OK) == 0)
		{
			free(path_tmp[0]);
			free(path_tmp);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free(path_tmp[0]);
	free(path_tmp);
	return (ft_strdup(arg));
}

char	*find_path(char *arg, char **env)
{
	int		i;
	char	**path_tmp;

	if (chech_arg(arg))
		return (ft_strdup(arg));
	i = 0;
	path_tmp = NULL;
	while (env[i])
	{
		if (ft_strcmp(env[i], "PATH="))
		{
			path_tmp = ft_split(env[i], ':');
			break ;
		}
		i++;
	}
	if (path_tmp == NULL)
		return (ft_strdup(arg));
	return (find_path_extra(path_tmp, arg));
}
