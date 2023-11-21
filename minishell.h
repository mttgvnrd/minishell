/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:59:09 by mgiovana          #+#    #+#             */
/*   Updated: 2023/09/19 12:59:21 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./src/libft/libft.h"
# include "./src/Printf/ft_printf.h"
# include "./src/GNL/get_next_line.h"
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>


# define INPUT 1
# define HEREDOC 2
# define OUTPUT 4
# define APPEND 8

typedef struct s_env
{
    char    *var;
    char    *value;
    int     index;
    struct s_env    *next;
} t_env;

typedef struct s_commands
{
    char    *from_file;
    char    *cmd;
    char    **hdocs_end;
    char    **args;
    char    **to_file;
    char    **full_cmd;
    int     input;
    int     output;
    int     redirect;
    struct s_env    *next;


}   t_commands;

typedef struct s_main
{
    char    **env;
    char    **env_path;
    char    *env_user;
    char    *actual_dir;
    char    *env_dir;
    char    *shell_line;
    int     stop_flag;
    int     shell_loop;
    int     first_fd[2];
    int     first_call;
    int     error_cmd;

}       t_main;
//variabile globale che salva l'attributo del terminale
typedef struct s_term
{
    struct termios  save_attr;
    int             status;
}           t_term;

struct termios g_save_attr;  /* Usato per contollare l input e creare una lista */

// MAIN
int		ft_open_quotes(char *input);
int		ft_init_shell(char **env);

//UTILS
char	**ft_double_realloc(char **str, int old_size, int new_size);
char	*ft_strjoin_free(char *s1, char *s2);
int	    ft_skip_spaces (char *str);
void	ft_free_double_str(char **str);
void    ctrl_1(int sig);
int     ft_count_lines(int fd);
//char    **dup_array(const char *array);

//PARSING
t_commands	*ft_check_input(char *str, t_env *env_lst);
char    ft_split_input(char *input);
char    *ft_cut(char *input, int *index);
t_commands	*ft_cmd_analyze(t_commands *cmd, char **full_cmds, t_env *env_list);
//////////////////////////////////////////DA FINIRE

//LEXER
char    **ft_lexer(char *input, t_env *env_lst);
char	*ft_token(char *str, char *in_put, int *index, t_env *env_list);

//INIT
void     ft_parse_init(char *str, t_env **env_lst);
t_env  *ft_get_env(char **env);
t_env  *ft_new_envnode(char *env, int index);
void	ft_remove_all_spaces(t_commands *cmd);
void	ft_remove_spaces(char **str);
int	    ft_check_list(t_commands *cmd);

//SIGNAL
void    ft_ctrl_ingore(int sig);
int		ft_set_terminal(void);

//INPUT

//UTILS 1
void	ft_add_env_lastcmd(t_commands *cmd, t_env *env_list);

//FREE
void	ft_free_cmdlist(t_commands **cmd);

//CMDSYSTEM
void	ft_convertsys(t_commands *cmd, t_env *envp);
char	**ft_getpath(t_env *envp);
int	    ft_checkpath(char *command, char **paths);
char	*ft_crate_path(char *path, char *command);

//SYS UTILS

int	ft_issyscmd(char *cmd, t_env *envp); 
int	ft_strcmp(char *s1, char *s2);
int	ft_isnonsyscmd(char *arg);

//EXE
void	ft_cmd_analysis(t_commands *cmd, t_env **env_list);//DA FINIRE

#endif
