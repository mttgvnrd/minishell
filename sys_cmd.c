#include "minishell.h"

char	*ft_mkpathcommand(char *path, char *command)
{
	char	*temp;
	char	*out;

	temp = ft_strjoin(path, "/");
	out = ft_strjoin(temp, command);
	free(temp);
	return (out);
}

int	ft_checkpaths(char *command, char **paths)
{
	int		i;
	char	*pathcommand;

	i = 0;
	if (!command || !paths)
		return (-1);
	while (paths[i])
	{
		pathcommand = ft_mkpathcommand(paths[i], command);
		if (access(pathcommand, X_OK) == 0)
			return (free(pathcommand), i);
		free(pathcommand);
		i++;
	}
	return (-1);
}

char	**ft_getpaths(t_env *envp)
{
	t_env	*tmp;
	char	**out;

	tmp = envp;
	while (tmp)
	{
		if (!strcmp("PATH", tmp->var))
		{
			out = ft_split(tmp->value, ':');
			return (out);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (NULL);
}

void	ft_convertsyscommands(t_commands *cmd, t_env *envp)
{
	char	**paths;
	int		pathnum;
	char	*temp;
	t_commands	*tmp;

	paths = ft_getpaths(envp);
	tmp = cmd;
	while (tmp)
	{
		if (!ft_isnonsyscmd(tmp->cmd))
		{
			pathnum = ft_checkpaths(tmp->cmd, paths);
			if (pathnum >= 0)
			{
				temp = ft_mkpathcommand(paths[pathnum], tmp->cmd);
				free(tmp->cmd);
				tmp->cmd = temp;
			}
		}
		tmp = tmp->next;
	}
	ft_free_double_str(paths);
}