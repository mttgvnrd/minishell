/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:46:26 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/21 14:46:29 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_env_lastcmd(t_commands *cmd, t_env *env_list)
//assicura che la variabile d'ambiente _ rifletta 
//sempre l'ultimo comando eseguito nel programma.
{
	t_env	*tmp_env;
	t_commands	*tmp_cmd;

	tmp_env = env_list;
	tmp_cmd = cmd;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->var, "_"))
		{
			if (tmp_env->value)
				free(tmp_env->value);
			if (tmp_cmd->next)
				tmp_env->value = ft_calloc(1, sizeof(char));
			else
				tmp_env->value = ft_strdup(cmd->cmd);
			return ;
		}
		tmp_env = tmp_env->next;
	}
}