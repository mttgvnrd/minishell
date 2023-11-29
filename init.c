/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:08:56 by mgiovana          #+#    #+#             */
/*   Updated: 2023/09/19 13:11:41 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//questa funzione crea un nodo della lista concatenata t_env 
//a partire da una stringa di variabile d'ambiente envp e un indice index.
t_env  *ft_new_envnode(char *env, int index)
{
    t_env  *node;
    char    **c;

    node = (t_env *) calloc(1, sizeof(t_env));
    if (!node)
        return(NULL);
    c = ft_split(env, '=');
    node->var = ft_strdup(c[0]);
	node->value = ft_strdup(c[1]);
	node->index = index;
	ft_free_double_str(c);
	return (node);
}

// crea una lista concatenata di tipo t_env a partire da un array di
// stringhe envp, dove ogni elemento dell'array rappresenta una variabile d'ambiente.
t_env  *ft_get_env(char **env)
{
    int     i;
    t_env   *head;
    t_env   *temp;

    i = 0;
    head = ft_new_envnode(env[i], i);
    if (!head)
        return (NULL);
    temp = head;
    while(env[++i])
    {
        temp->next = ft_new_envnode(env[i], i);
        if (!temp)
            return(NULL);
        temp = temp->next;
    }
    return (head);
}

//Questa funzione verifica se ci sono comandi vuoti nella lista di comandi (t_commands).
int	ft_check_list(t_commands *cmd)
{
	t_commands	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->cmd)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_remove_spaces(char **str)
{
	int		count2;
	char	*tmp;

	count2 = 0;
	while (!ft_isascii(str[0][count2]) || str[0][count2] == ' '
		|| str[0][count2] == '\t' || str[0][count2] == '\v')
		count2 ++;
	if (count2)
	{
		tmp = ft_strdup(&str[0][count2]);
		free(str[0]);
		str[0] = tmp;
	}
}

//serve per rimuovere spazi in eccesso all'inizio 
//di ciascun comando (cmd) in una lista di comandi (t_commands)
void	ft_remove_all_spaces(t_commands *cmd)
{
	t_commands	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->cmd)
			return ;
		if (!ft_isascii(tmp->cmd[0]) || tmp->cmd[0] == ' '
			|| tmp->cmd[0] == '\t' || tmp->cmd[0] == '\v')
			ft_remove_spaces(&tmp->cmd);
		tmp = tmp->next;
	}
}

    /* Used to check the input and pass it to the parsing and cutting
 functions to get back either a linked list with all the command original
 just one command in a node */ 
void     ft_parse_init(char *str, t_env **env_lst)
{
	t_commands	*cmd;
	int		i;

	i = 0;
	i += ft_skip_spaces(str);
	if (!str[i])
		return ;
	cmd = ft_check_input(&str[i], *env_lst);
	free(str);
	if (!cmd)
	{
		printf("minihell: syntax error near unexpected token `%s' \n", str);
		return ;
	}
	if (!cmd->cmd || (!strlen(cmd->cmd)) | ft_check_list(cmd))
		return (ft_free_cmdlist(&cmd));
	ft_remove_all_spaces(cmd);
	ft_convertsys(cmd, *env_lst);
	ft_add_env_lastcmd(cmd, *env_lst);
	ft_init_exe(cmd, env_lst);
}
