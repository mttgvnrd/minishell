/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:49:59 by mgiovana          #+#    #+#             */
/*   Updated: 2023/09/28 14:50:04 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// disabilito comandi che nella shell non funzionano 
void	ft_ctrl_ingore(int sig)
{
	write (1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	return ((void)sig);
}

/*salvo i valori originali del termianle,
e cosi posso modificarli per disabilitare il messaggio ^C */
int	ft_set_terminal(void)
{
	struct termios	attr_copy;
	int				error;

	error = 0;
	error = tcgetattr(STDIN_FILENO, &g_save_attr);
	attr_copy = g_save_attr;
	attr_copy.c_lflag &= ~ECHOCTL;
	error = tcsetattr(STDIN_FILENO, TCSANOW, &attr_copy);
	return (error);
}
