/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:26:51 by mgiovana          #+#    #+#             */
/*   Updated: 2023/10/31 12:26:53 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// alloca memoria per una nuova struttura t_commands rappresentante un comando. 
//In seguito, copia il nome del comando e gli argomenti dall'array 
//array_cmds nella nuova struttura commands
t_commands *ft_parser(char **array_cmds)
{
	t_commands	*cmd;
	int		count;

	cmd = (t_commands *)ft_calloc(1, sizeof(t_commands));
	if (!cmd)
		return (NULL);
	if (!array_cmds || ft_check_redirect(cmd, array_cmds))
		return (free(cmd), NULL);
	count = 0;
	if (array_cmds[count])
		cmd->cmd = ft_strdup(array_cmds[count]);
	cmd->args = (char **)ft_calloc(1, sizeof(char *));
	if (!cmd->args)
		return (NULL);
	cmd->args = ft_check_args(array_cmds[count + 1], cmd->args);
	while (array_cmds[++count])
	{
		cmd->args[count - 1] = ft_strdup(array_cmds[count]);
		cmd->args = ft_double_realloc(cmd->args, count, count + 1);
	}
	ft_free_double_str(array_cmds);
	return (cmd);
}


char    *ft_cut(char *input, int *index)
{
    int     count;
    char    *str;
    char    qoutes;

    count = *index - 1;
    str = NULL;
    while (input[++count] && input[count] != '|')
	{
		if (input[count] == '"' || input[count] == '\'')
		{
			qoutes = input[count];
			str = ft_strjoin_free(str, ft_substr(&input[count], 0, 1));
			while (input[++count] && input[count] != qoutes)
				str = ft_strjoin_free(str, ft_substr(&input[count], 0, 1));
		}
		str = ft_strjoin_free(str, ft_substr(&input[count], 0, 1));
	}
    if (!input[count])
        count --;
    *index = count;
    return(str);
}

char    **ft_split_input(char *input)
{
    int     i;
    int     count;
    char    **cmds;
    char    *str;

    str = NULL;
    count = -1;
    i = -1;
    cmds = (char **)ft_calloc(1, sizeof(char *));
    if (!cmds)
        return (NULL);
    while (input[++count])
    {
        str = ft_cut(input, &count);
        if (str)
        {
            cmds[++i] = ft_strdup(str);
            cmds = ft_double_realloc(cmds, i + 1, i + 2);
            free(str);
        }
    }
    return(cmds);
}

//La funzione scorre l'array array_cmds, estrae e analizza ogni singolo 
//comando utilizzando la funzione ft_parser. Ogni comando viene poi aggiunto 
//alla lista concatenata dei comandi rappresentata dalla struttura t_commands
t_commands	*ft_cmd_analyze(t_commands *cmd, char **array_cmds, t_env *env_lst)
{
	t_commands	*tmp;
	int		count;
	int		len;

	count = -1;
	if (!cmd)
		return (cmd);
	tmp = cmd;
	while (array_cmds[++count])
	{
		len = ft_skip_spaces(array_cmds[count]);
		tmp->next = ft_parser(ft_lexer(&array_cmds[count][len], env_lst));
		if (!tmp->next)
		{
			ft_free_cmdlist(&cmd);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (cmd);
}

t_commands	*ft_check_input(char *str, t_env *env_lst)
{
    int     len;
    int     i;
    char    **array_cmds;
    t_commands  *cmd;

    len = 0;
    i = 0;
    array_cmds = ft_split_input(str);
    while (array_cmds[len])
        len++;
    cmd = ft_parser(ft_lexer(array_cmds[i], env_lst));
    if (len > 1)
        cmd = ft_cmd_analyze(cmd, array_cmds, env_lst);
    ft_free_double_str(array_cmds);
    return(cmd);
}
