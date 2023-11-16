/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:42:58 by mgiovana          #+#    #+#             */
/*   Updated: 2023/10/25 14:43:01 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char    **dup_array(const char *array)
{
    char    **clone;
    int     i;

    i = 0;
    while(array[i] != NULL)
        i++;
    clone = malloc(sizeof(char *) * (i + 1));
    i = 0;
    if (clone != NULL)
    {
        while (array[i] != '\0')
        {
            clone[i] = ft_strdup(array[i]);
            i++;
        }
    }
    return(clone);
}*/

/* rialloca memoria per la stringa a doppio puntatore */
char	**ft_double_realloc(char **str, int old_size, int new_size)
{
	char	**tmp;
	int		count;

	tmp = (char **)ft_calloc(new_size, sizeof(char *));
	count = 0;
	while (count < old_size)
	{
		tmp[count] = ft_strdup(str[count]);
		free(str[count]);
		count ++;
	}
	free(str);
	return (tmp);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*nstr;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	nstr = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1, len_s1 + 1);
	ft_strlcpy(&nstr[len_s1], s2, len_s2 + 1);
	free(s1);
	free(s2);
	return (nstr);
}

/* Ignora gli spazi e ritorna il punto in cui non ci sono piu*/
int	ft_skip_spaces (char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13)
			|| str[i] == 32))
		i ++;
	return (i);
}

void	ft_free_double_str(char **str)
{
	int	count;

	count = 0;
	if (!str)
		return ;
	while (str[count])
	{
		free(str[count]);
		count ++;
	}
	free(str);
}

void    ctrl_1(int sig)
{
	struct termios	new;

	tcgetattr(0, &new);
	if (sig)
		new.c_lflag |= ECHOCTL;
	else
		new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}

int     ft_count_lines(int fd)
{
	int		i;
	char	*line;

	if (fd < 0)
		return (-1);
	i = 1;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (i);
}