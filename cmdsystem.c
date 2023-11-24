/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdsystem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:17:27 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/20 14:17:31 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_path(char *path, char *command)
//costruisce il percorso completo di un comando
// combinando un percorso e un comando
{
	char	*temp;
	char	*out;

	temp = ft_strjoin(path, "/");
	out = ft_strjoin(temp, command);
	free(temp);
	return (out);
}

int	ft_checkpath(char *command, char **paths)
//cerca il comando in una lista di percorsi e verifica se 
// e accessibile
{
	int		i;
	char	*pathcommand;

	i = 0;
	if (!command || !paths)
		return (-1);
	while (paths[i])
	{
		pathcommand = ft_create_path(paths[i], command);
		if (access(pathcommand, X_OK) == 0)
			return (free(pathcommand), i);
		free(pathcommand);
		i++;
	}
	return (-1);
}

char	**ft_getpath(t_env *envp)
//cerca PATH nelle variabili di ambiente e lo copia
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

void	ft_create_fullcmd(t_commands *cmd)
//costruisce un array di stringhe contenente il comando 
//principale e i suoi argomenti
{
	char	**full_cmd;
	int		count;

	while (cmd)
	{
		count = 0;
		if (!cmd->cmd)
			return ;
		full_cmd = (char **)ft_calloc(1, sizeof(char *));
		full_cmd[count] = ft_strdup(cmd->cmd);
		full_cmd = ft_double_realloc(full_cmd, count + 1, count + 2);
		while (cmd->args && cmd->args[count])
		{
			full_cmd[count + 1] = ft_strdup(cmd->args[count]);
			count ++;
			full_cmd = ft_double_realloc(full_cmd, count + 1, count + 2);
		}
		cmd->full_cmd = full_cmd;
		if (cmd->next)
			cmd = cmd->next;
		else
			return ;
	}
}

void	ft_convertsys(t_commands *cmd, t_env *envp)
//verifica se ciascun comando è di sistema o meno, e se è 
//di sistema, sostituisce il comando con il percorso completo
{
	char    **paths;
	int		path_num;
	char	*temp;
	t_commands	*tmp;

	paths = ft_getpath(envp);
	tmp = cmd;
	while (tmp)
	{
		if (!ft_isnonsyscmd(tmp->cmd))
		{
			path_num = ft_checkpath(tmp->cmd, paths);
			if (path_num >= 0)
			{
				temp = ft_create_path(paths[path_num], tmp->cmd);
				free(tmp->cmd);
				tmp->cmd = temp;
			}
		}
		tmp = tmp->next;
	}
	ft_free_double_str(paths);
	ft_create_fullcmd(cmd);
}
