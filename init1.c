#include "minishell.h"

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

//libera la struttura t_commands
void	ft_free_cmdlist(t_commands **cmd)
{
	t_commands	*cpy;

	cpy = *cmd;
	while (cpy)
	{
		*cmd = (*cmd)->next;
		if (cpy->cmd)
			free(cpy->cmd);
		if (cpy->args)
			ft_free_double_str(cpy->args);
		if (cpy->full_cmd)
			ft_free_double_str(cpy->full_cmd);
		if ((cpy->redirect & INPUT))
			free(cpy->from_file);
		if ((cpy->redirect & HEREDOC))
			ft_free_double_str(cpy->hdocs_end);
		if ((cpy->redirect & OUTPUT) || (cpy->redirect & APPEND))
			ft_free_double_str(cpy->to_file);
		free(cpy);
		cpy = *cmd;
	}
}

//assicura che la variabile d'ambiente _ rifletta 
//sempre l'ultimo comando eseguito nel programma.
void	ft_add_env_lastcmd(t_commands *cmd, t_env *env_list)
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