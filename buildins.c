/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:56:19 by mgiovana          #+#    #+#             */
/*   Updated: 2024/01/03 11:42:16 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (tmp->var && !tmp->custom && tmp->value)
			printf("%s=%s\n", tmp->var, tmp->value);
		else if (tmp->var && !tmp->custom && !tmp->value)
			printf("%s=\n", tmp->var);
		if (tmp->next)
			tmp = tmp->next;
		else
			return (0);
	}
	return (0);
}

void	ft_chdir_envp(t_env *envp)
{
	t_env	*tmp;
	char	*oldpwd;
	int		pwdset;

	pwdset = 0;
	tmp = envp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, "PWD") && !pwdset)
		{
			oldpwd = tmp->value;
			tmp->value = getcwd(NULL, 0);
			pwdset = 1;
			tmp = envp;
		}
		if (!ft_strcmp(tmp->var, "OLDPWD") && pwdset)
		{
			free(tmp->value);
			tmp->value = oldpwd;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			return ;
	}
}

int	ft_cd(char **args, t_env *envp)
{
	struct stat	st;
	int			chdirrt;
	const char	*home;
	
	if (!args || args[0] == NULL)
	{	
			home = getenv("HOME");
			if (home == NULL)
				return (perror("cd"), 1);
			chdirrt = chdir(home);
			if (chdirrt == -1)
				return (perror("cd"), 1);
			else
				ft_chdir_envp(envp);
	}	
	
	else
	{
		if (stat(args[0], &st) != 0)
		{
			return (printf("cd: No such file or directory: %s\n",
					args[0]), 1);
		}
		else if (!S_ISDIR(st.st_mode))
			return (printf("cd: %s: Not a directory\n", args[0]), 1);
		else
		{
			chdirrt = chdir(args[0]);
			if (chdirrt == -1)
				return (perror("cd"), 1);
			else
				ft_chdir_envp(envp);
		}
	}
	return (0);
}

//check su -n
int	ft_is_dash_n(char	*arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	i = 0;
	nl = 1;
	if (!args || args[0] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (ft_is_dash_n(args[0]))
	{
		nl = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		if (args[i + 1] == NULL)
			printf("%s", args[i++]);
		else
			printf("%s ", args[i++]);
	}	
	if (nl == 1)
		printf("\n");
	return(0);
}
