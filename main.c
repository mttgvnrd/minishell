/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:50:38 by mgiovana          #+#    #+#             */
/*   Updated: 2023/09/19 13:06:56 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// controllo sulle ('') e (""), verifica se ci sono virgolette aperte e non chiuse
// se close ha un valore vuol dire che non sono state chiuse 
// le vigolette e quindi stampera un mex di errore
int		ft_open_quotes(char *input)
{
	char	divid;
	int		index;
	int		close;

	index = -1;
	close = 0;
	while (input[++index])
	{
		if (input[index] == '"' || input[index] == '\'')
		{
			if (!close)
			{
				close = 1;
				divid = input[index];
			}
			else if (input[index] == divid)
				close = 0;
		}
	}
	if (close)
	{
		free(input);
		return (printf("minishell: unclosed qoute detected.\n"), 1);
	}
	return (0);
}

//studia
void	ft_free_envlist(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		*env_list = (*env_list)->next;
		if (tmp->var)
			free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = *env_list;
	}
}

//studia
void	ft_exit_minihell(t_cmds *cmd, t_env *env_list)
{
	int	exitcode;

	if (!cmd->args)
		exitcode = 0;
	else
	{
		if (cmd->args[0] && ft_isdigit(cmd->args[0][0]))
			exitcode = ft_atoi(cmd->args[0]);
		else
		{
			exitcode = 0;
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->args[0]);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_save_attr);
	ft_free_cmdlist(&cmd);
	ft_free_envlist(&env_list);
	write(1, "exit\n", 5);
	clear_history();
	exit(exitcode);
}

/* Used to display the prompt and read the input from the user */
int		ft_init_shell(char **env)
{
	char	*str;
	t_env	*env_lst;

	env_lst = ft_get_env(env);
	while (1)
	{
		str = readline("minishell ");
		if (!str)
			str = (ft_strdup("exit"));
		add_history(str);
		if (ft_open_quotes(str))
			continue;
		ft_parse_init(ft_strdup(str) , &env_lst);
		free(str);
	}

}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
    signal(SIGINT, ft_ctrl_ingore);
	if (ft_set_terminal())
		exit(1);
	ft_init_shell(env);
}	
