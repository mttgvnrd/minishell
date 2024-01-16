/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:13:46 by mgiovana          #+#    #+#             */
/*   Updated: 2024/01/16 17:13:48 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalididentifier(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	else
		return (0);
}

int	ft_checkforwrongargs(char **args)
{
	int		i;
	int		returnval;

	i = 0;
	returnval = 0;
	while (args[i])
	{
		if (!ft_isvalididentifier(args[i][0]))
			returnval += printf(" export: `%s': not a valid identifier\n",
					args[i]);
		i++;
	}
	if (returnval > 0)
		return (1);
	else
		return (0);
}

void	ft_setindexprinted(t_env *envp, int index, int *indexprinted)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (index == tmp->index)
		{
			indexprinted[tmp->index] = 1;
			return ;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			return ;
	}
}
