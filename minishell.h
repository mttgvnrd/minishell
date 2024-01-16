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
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <wait.h>
# include <sys/stat.h>

# define MEX "minishell: syntax error near unexpected token"
//Pipe action
# define READ 0
//Pipe action
# define WRITE 1

# define INPUT 1
# define HEREDOC 2
# define OUTPUT 4
# define APPEND 8

typedef struct s_env
{
	char				*var;
	char				*value;
	int					index;
	int					exit_status;
	int					custom;
	struct s_env		*next;
}	t_env;

typedef struct s_commands
{
	char				*from_file;
	char				*cmd;
	char				**hdocs_end;
	char				**args;
	char				**to_file;
	char				**full_cmd;
	int					input;
	int					output;
	int					redirect;
	struct s_commands	*next;

}	t_commands;

typedef struct s_pid
{
	pid_t				pid;
	struct s_pid		*next;
}	t_pid;

typedef struct s_exe
{
	int					pipe1[2];
	int					pipe2[2];
	int					trigger;
	int					pipe_shift;
}	t_exe;

typedef struct s_main
{
	char				**env;
	char				**env_path;
	char				*env_user;
	char				*actual_dir;
	char				*env_dir;
	char				*shell_line;
	int					stop_flag;
	int					shell_loop;
	int					first_fd[2];
	int					first_call;
	int					error_cmd;

}	t_main;
//variabile globale che salva l'attributo del terminale
typedef struct s_term
{
	struct termios		save_attr;
	int					status;
}	t_term;

extern struct termios	g_save_attr;

// MAIN
int			ft_open_quotes(char *input);
int			ft_init_shell(char **env);
void		ft_exit_minihell(t_commands *cmd, t_env *env_list);
void		ft_free_envlist(t_env **env_list);
//UTILS
char		**ft_double_realloc(char **str, int old_size, int new_size);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_skip_spaces(char *str);
void		ft_free_double_str(char **str);
void		ctrl_1(int sig);
int			ft_count_lines(int fd);
int			ft_go_home(int chdirrt, t_env *envp);
//PARSING
t_commands	*ft_check_input(char *str, t_env *env_lst);
char		**ft_split_input(char *input);
char		*ft_cut(char *input, int *index);
t_commands	*ft_cmd_analyze(t_commands *cmd, char **full_cmds, t_env *env_list);
t_commands	*ft_parser(char **array_cmds);
//LEXER
char		**ft_lexer(char *input, t_env *env_lst);
char		*ft_token(char *str, char *in_put, int *index, t_env *env_list);
//INIT / INIT 2
void		ft_parse_init(char *str, t_env **env_lst);
t_env		*ft_get_env(char **env);
t_env		*ft_new_envnode(char *env, int index);
void		ft_remove_all_spaces(t_commands *cmd);
int			ft_check_list(t_commands *cmd);
void		ft_remove_spaces(char **str);
void		ft_add_env_lastcmd(t_commands *cmd, t_env *env_list);
void		ft_free_cmdlist(t_commands **cmd);
//SIGNAL
void		ft_ctrl_ingore(int sig);
int			ft_set_terminal(void);
//UTILS 1
char		**ft_check_args(char *arg, char **cmd_args);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
//CMDSYSTEM
void		ft_convertsys(t_commands *cmd, t_env *envp);
char		**ft_getpath(t_env *envp);
int			ft_checkpath(char *command, char **paths);
char		*ft_create_path(char *path, char *command);
//SYS UTILS
int			ft_issyscmd(char *cmd, t_env *envp);
int			ft_strcmp(char *s1, char *s2);
int			ft_isnonsyscmd(char *arg);
//EXE
void		ft_init_exe(t_commands *cmd, t_env **env_list);
int			ft_execute_buildin(t_commands *cmd, t_env **env_list);
int			ft_cmd_size(t_commands *cmd);
char		**ft_create_env_array(t_env	*env_list);
//ChildExe
void		executor(t_commands *cmd, t_env *env_list);
void		exe_command(t_commands *current_cmd, t_exe *exec_data,
				t_env *env_list, t_pid **pids);
int			ft_child_processes(t_pid *pids, int*exit_status);
void		add_pid_to_list(pid_t pid, t_pid **pids);
//HEREDOC
int			ft_here_doc(char **hdocs_end, t_commands *cmd);
int			ft_read_hdocs(char *hdocs_end);
//FD REDIR
void		ft_infile_fd(t_commands *cmd);
void		ft_outfile_fd(t_commands *cmd, char *to_file, int redirect);
void		ft_execute_redirection(t_commands *cmd);
//MANAGE REDIR / MANAGE REDIR1
char		*ft_add_io_file(char *old_file, char *new_file, int len);
char		**ft_many_redirect(char **old_files, char *new_file, int len);
void		ft_arrange_table(char **table, int index, int len);
int			ft_add_redirection(char **table, t_commands *cmd, int index,
				int len);
int			ft_get_redirection(char *in_put);
int			ft_check_redirect(t_commands *cmd, char **cmd_table);
//PIPE
void		set_in_fd(t_exe *exec_data, int fd);
void		initiate_pipe(t_exe *exec_data);
void		set_out_fd(t_exe *exec_data, int fd);
void		rotator(t_exe *exec_data);
///BUILTIN
int			is_builtin(t_commands *cmd);
int			check_or_exec_builtin(t_commands *cmd, t_exe *exec_data,
				t_env *env_list);
//BUILDINS
int			ft_echo(char **args);
int			ft_is_dash_n(char *arg);
int			ft_env(t_env *envp);
void		ft_chdir_envp(t_env *envp);
int			ft_cd(char **args, t_env *envp);
//BUILDINS 2
int			ft_pwd(void);
int			ft_unset(char **args, t_env **envp);
void		ft_unset_loop(t_env *tmp, t_env *tmp_last, t_env **envp, char *arg);
void		ft_rearrange_indexes(t_env *envp);
//EXPORT
char		*ft_getvarname(char *arg);
char		*ft_getvarvalue(char *arg);
void		ft_export_arg(char **args, t_env **envp, t_env *tmp, int i);
void		ft_listvariables(t_env *envp);
int			ft_export(char **args, t_env **envp);
//EXPORT 1
int			ft_listinenv(char *arg);
void		ft_addnewnode(char *arg, t_env *tmp, t_env **envp);
int			ft_check_and_edit_existing_var(char **args, t_env *tmp, int i);
//EXPORT 2
int			ft_isbeforeinalph(char *varname, char *tmpvar);
int			ft_isnotprinted(t_env *envp, int *indexprinted, int withcostumvars);
void		ft_printinorder(t_env *envp, int *indexprinted);
int			ft_checklistlen(t_env *envp);
void		ft_printnextalpha(t_env *envp, int *indexprinted);
//EXPORT 3
int			ft_isvalididentifier(char c);
int			ft_checkforwrongargs(char **args);
void		ft_setindexprinted(t_env *envp, int index, int *indexprinted);
//FORK
void		dup2_and_close(int from, int to);
int			fork_process(t_commands *cmd, t_exe *exec_data, t_env *env_list);
//SYS CMD
void		ft_convertsyscommands(t_commands *cmd, t_env *envp);
char		**ft_getpaths(t_env *envp);
char		*ft_mkpathcommand(char *path, char *command);
int			ft_checkpaths(char *command, char **paths);

#endif
