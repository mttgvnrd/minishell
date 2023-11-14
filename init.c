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

t_env  *ft_new_envnode(char *env, int index)
//questa funzione crea un nodo della lista concatenata t_env 
//a partire da una stringa di variabile d'ambiente envp e un indice index.
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

t_env  *ft_get_env(char **env)
// crea una lista concatenata di tipo t_env a partire da un array di
// stringhe envp, dove ogni elemento dell'array rappresenta una variabile d'ambiente.
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

    /* Used to check the input and pass it to the parsing and cutting
 functions to get back either a linked list with all the command original
 just one command in a node */ 
int     ft_parse_init(char *str, t_env **env_lst)
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
	if (!cmd->cmd || !strlen(cmd->cmd) | ft_checkforgarbage(cmd))
		return (ft_free_cmdlist(&cmd));
	ft_removesurplusspaces(cmd);
	ft_convertsyscommands(cmd, *env_lst);
	ft_create_fullcmd(cmd);
	ft_add_env_lastcmd(cmd, *env_lst);
	ft_cmd_analysis(cmd, env_lst);
}