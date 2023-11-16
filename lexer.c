/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:55:45 by mgiovana          #+#    #+#             */
/*   Updated: 2023/11/14 14:23:15 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*ft_expansion(char *str, t_env *env_list)
//studia
{
	t_env	*tmp;

	tmp = env_list;
	if (!str)
		return (ft_strdup("$"));
	if (!ft_strcmp(str, "?"))
	{
		free(str);
		return (ft_itoa(env_list->exit_status));
	}
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->var))
		{
			free(str);
			if (!env_list->custom && !tmp->value)
				return (ft_strdup("\n"));
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	free(str);
	return (ft_strdup(""));
}

char	*ft_getenv_var(char *in_put, int *index, t_env *env_list)
//studia
{
	char	*str;
	int		count;

	count = *index;
	str = NULL;
	while (in_put[++count] && (in_put[count] == '_' || in_put[count] == '?'
			|| ft_isalnum(in_put[count])))
		str = ft_strjoin_free(str, ft_substr(&in_put[count], 0, 1));
	*index = count - 1;
	return (ft_expansion(str, env_list));
}

char	*ft_inside_qoutes(char *str, char *in_put, int *index, t_env *env_list)
//studia
{
	char	*tmp;
	char	divid;
	int		count;

	count = *index;
	divid = in_put[count];
	while (in_put[++count] && in_put[count] != divid)
	{
		tmp = NULL;
		if (in_put[count] == '$' && divid == '"')
			tmp = ft_getenv_var(in_put, &count, env_list);
		if (tmp)
			str = ft_strjoin_free(str, tmp);
		else
			str = ft_strjoin_free(str, ft_substr(&in_put[count], 0, 1));
	}
	*index = count;
	return (str);
}

char	*ft_token(char *str, char *in_put, int *index, t_env *env_list)
//studia
{
	int		cnt;

	cnt = *index;
	while (in_put[cnt] && in_put[cnt] != ' '
		&& in_put[cnt] != '<' && in_put[cnt] != '>')
	{
		if (in_put[cnt] == '"' || in_put[cnt] == '\'')
			str = ft_inside_qoutes(str, in_put, &cnt, env_list);
		else if (in_put[cnt] == '$')
			str = ft_strjoin_free(str, ft_getenv_var(in_put, &cnt, env_list));
		else
			str = ft_strjoin_free(str, ft_substr(&in_put[cnt], 0, 1));
		cnt ++;
	}
	cnt += ft_isnspace_indx(&in_put[cnt]) - 1; //here
	*index = cnt;
	return (str);
}

char    **ft_lexer(char *input, t_env *env_lst)
//studia
{
    int     i;
    int     cnt;
    char    *str;
    char    **cmds;

    i = -1;
    cnt = -1;
    cmds = (char **)calloc(1, sizeof(char *));
    if (!cmds || !input)
        return (NULL);
    while (input[++cnt])
    {
        str = NULL;
        while (input[cnt] && (input[cnt] == '<' || input[cnt] == '>'))
		{
			str = ft_strjoin_free(str, ft_substr(&input[cnt], 0, 1));
			cnt ++;
		}
		str = ft_token(str, input, &cnt, env_lst);// ft_tokenize
		cmds[++i] = ft_strdup(str);
		cmds = ft_double_realloc(cmds, i + 1, i + 2);
		free(str);
	}
	return (cmds);
}    
