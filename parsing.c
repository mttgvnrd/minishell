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

t_commands *ft_parser(char **array_cmds)
{

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

char    ft_split_input(char *input)
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
}
