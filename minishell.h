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
# include <errno.h>


# define READ 0
# define WRITE 1

# define INPUT 1
# define HEREDOC 2
# define OUTPUT 4
# define APPEND 8

typedef struct s_env
{
    char    *var;
    char    *value;
    int     index;
    int     exit_status;
    int     custom;
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
    struct s_commands    *next;

}   t_commands;

typedef struct s_pid
{
    pid_t       pid;
    struct s_pid    *next;
    int     pipe_shift;
}   t_pid;


typedef struct s_exe
{
    int     pipe1[2];
    int     pipe2[2];

}   t_exe;


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
char    **ft_split_input(char *input);
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
char	**ft_check_args(char *arg, char **cmd_args);

//FREE
void	ft_free_cmdlist(t_commands **cmd);

//CMDSYSTEM
void	ft_convertsys(t_commands *cmd, t_env *envp);
char	**ft_getpath(t_env *envp);
int	    ft_checkpath(char *command, char **paths);
char	*ft_create_path(char *path, char *command);

//SYS UTILS

int	ft_issyscmd(char *cmd, t_env *envp); 
int	ft_strcmp(char *s1, char *s2);
int	ft_isnonsyscmd(char *arg);

//EXE
void	ft_init_exe(t_commands *cmd, t_env **env_list);

//Executor 1
void	executor(t_commands *cmd, t_env *env_list);
void	execute_command(t_commands *current_cmd, t_exe *exec_data, t_env *env_list, t_pid **pids);
int 	wait_for_child_processes(t_pid	*pids, int	*exit_status);
void	add_pid_to_list(pid_t pid, t_pid **pids);

//HEREDOC
int	ft_here_doc(char **hdocs_end, t_commands *cmd);
int	ft_read_hdocs(char *hdocs_end);

//FD REDIR
void	ft_infile_fd(t_commands *cmd);
void	ft_outfile_fd(t_commands *cmd, char *to_file, int redirect);
void	ft_execute_redirection(t_commands *cmd);

//MANAGE REDIR / MANAGE REDIR1
char	*ft_add_io_file(char *old_file, char *new_file, int len);
char	**ft_many_redirect(char **old_files, char *new_file, int len);
void	ft_arrange_table(char **table, int index, int len);
int	    ft_add_redirection(char **table, t_commands *cmd, int index, int len);
int	    ft_get_redirection(char *in_put);
int	    ft_check_redirect(t_commands *cmd, char **cmd_table);

//PIPE
void	set_in_fd(t_exe *exec_data, int fd);
void	initiate_pipe(t_exe *exec_data);
void	set_out_fd(t_exe *exec_data, int fd);
void	rotator(t_exe *exec_data);

///BUILTIN
int	is_builtin(t_commands *cmd);
int	check_or_exec_builtin(t_commands *cmd, t_exe *exec_data, t_env *env_list);
static void	dup_pipe(t_exe *exec_data, int *original_input, int *original_output)


#endif
