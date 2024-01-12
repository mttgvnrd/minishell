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

//Cerca la variabile d'ambiente corrispondente nella lista delle variabili d'ambiente
//Se la trova, restituisce il suo valore. Se non la trova, restituisce una stringa vuota
char	*ft_expansion(char *str, t_env *env_list)
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

//estrae e restituisce il valore di una variabile d'ambiente dalla stringa di input
char	*ft_getenv_var(char *in_put, int *index, t_env *env_list)
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

//gestisce la parte di una stringa racchiusa tra virgolette singole o doppie
char	*ft_inside_qoutes(char *str, char *in_put, int *index, t_env *env_list)
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

//estrase il token all interno della stringa di input
char	*ft_token(char *str, char *in_put, int *index, t_env *env_list)
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
	cnt += ft_skip_spaces(&in_put[cnt]) - 1;
	*index = cnt;
	return (str);
}

//tokenizza l'intera stringa di input
//restituisce l'array cmds, che rappresenta i token dell'input
char    **ft_lexer(char *input, t_env *env_lst)
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
		str = ft_token(str, input, &cnt, env_lst);
		i++;
	//	printf("%s , %d\n", str, i);
		if (str)
			cmds[i] = ft_strdup(str);
		else
			cmds[i] = ft_strdup(" ");
		cmds = ft_double_realloc(cmds, i + 1, i + 2);
		free(str);
	}
	return (cmds); 
}
	   
       // if (str[0] == '"' && str[1] == '"' && str[2] == '\0')
	   
	   
	   
	   
	   
	   
	   
	   
	   
	    /*while (input[cnt] && (input[cnt] == '<' || input[cnt] == '>'))
		{
			str = ft_strjoin_free(str, ft_substr(&input[cnt], 0, 1));
			cnt ++;
		}
		str = ft_token(str, input, &cnt, env_lst);
		i++;
		printf("%s, %d\n", str, i);
        if (str[0] == '"' && str[1] == '"' && str[2] == '\0')
			cmds[i] = ft_strdup(" ");
		else
			cmds[i] = ft_strdup(str);//////////////
		printf("456\n");
		cmds = ft_double_realloc(cmds, i + 1, i + 2);				
		free(str);
		printf("00\n");
	}
	return (cmds);
}    */