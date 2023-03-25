/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:20:30 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/25 19:50:47 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdlib.h>
# include <limits.h>
# include <termios.h>

# define READ_END		0  /* index pipe extremo escritura */
# define WRITE_END		1  /* index pipe extremo lectura */
# define BUFFER_SIZE	1

typedef struct s_quotes
{
	int		flag_d;
	int		flag_s;
	char	*join_str;
}	t_quotes;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char	*key;
	char	*file;
	char	*type;
	int		fd;
}	t_redir;

typedef struct s_pipe
{
	char			**full_cmd;
	char			*path;
	int				fd[2];
	t_redir			*redir;
	int				num_redi;
	int				wait;
	struct s_pipe	*next;
	struct s_pipe	*before;
}	t_pipe;

typedef struct s_cmd
{
	struct s_env	*env;
	char			**cmd;
	char			*cmd_line;
	char			*readl;
	int				num_pipes;
	int				save_stdin;
	int				save_stdout;
	struct s_pipe	*pipe;
	struct s_redir	*redir;
}	t_cmd;

typedef struct s_shell
{
	int				quit_status;
	int				pid;
	struct termios	save;
}	t_shell;

t_shell	g_shell;

//main.c
int		check_minishell(t_cmd *cmd);
void	run_minishell(t_cmd *cmd);

//save_cmds.c
int		save_cmds(t_cmd *cmd);
char	**save_cmd_redir(char *s, char **sp, int *j, t_redir **pipe_redir);
int		error_pipe_redir(t_pipe *pipe);
int		count_redirections(char *s);
int		ft_fin_cmds(t_pipe *pipe, t_cmd *cmd, char **sp2, char **sp);

//save_redir.c
void	save_redir(char *str, char *next, int *flag, t_redir *redir);
void	save_redir_append(char *str, char *next, int *flag, t_redir *redir);
void	save_redir_write(char *str, char *next, int *flag, t_redir *redir);
void	save_redir_read(char *str, char *next, int *flag, t_redir *redir);
void	save_redir_readline(char *str, char *next, int *flag, t_redir *redir);

//empty_or_delete_redir.c
char	**delete_redirection(char *sp, int *len);
int		save_empty(t_cmd *cmd);
char	**fill_empty(void);
int		delete_redir_len(char **s, int *len);
int		init_redir_size(t_pipe **pipe, char **sp);

//init.c
void	init_cmd(t_cmd *cmd);
void	init_quotes_flags(t_quotes *quotes);
t_redir	init_redirection(char *file, char *type, char *key);
int		init_minishell(int argc, char **argv, char **env, t_cmd	*cmd);

//checks.c
void	check_quotes_flags(t_quotes *quotes, char c);
int		is_quotes_opened(char *s);
int		is_two_pipes(char *s);
int		is_open_pipe(char *s);
int		check_init_params(int argc, char **argv);

//checks2.c
int		check_spaces(char *readl);
int		export_check(char *val, char *str, char *cmd);
void	ft_control(char *readl, t_quotes *quotes, int i);
int		is_digit(char *s);

//check3.c
int		is_fin_redirection(char *s);
void	redirections_find_space(char *s, int i, int *j);
void	ft_status(int status);
void	ft_status_heredoc(int status);

//utils.c
char	*find_change_str(char *s, t_env *env);
int		find_str(char c, char *s);
int		find_fin_str(char *s, int i);
int		join_split(t_cmd *cmd);
int		ft_strcmp(char *s1, char *s2);

//error.c
void	access_error(char *input);
void	pipe_error(char *error, int num);
void	execve_error(char *cmd);
int		print_error(char *s, int *i);
int		redirections_error(char *s, int num);

//error2.c
void	error_cd_relative_path(char *str);
int		error_open_file(char *str);
int		error_export(char *str, char *cmd);

//split.c
char	**split(char const *s, char c);
char	**subsplit(char **sp, int start, int len);

//linecontrol.c
int		line_parse(t_cmd *cmd, t_env *envp);
char	*prepare_split(char *readl);
void	expand(char **s, t_env *env);
char	*expand_dolar(char **s, t_env *env, t_quotes *quotes);
void	dollar_exchange(char *s, int *i, t_quotes *quotes, t_env *env);

//expand_utils.c
char	*change_quitvalue(char *s, int *i, char *join_str);
char	*expand_virgulilla(char**s, t_env *env, t_quotes *quotes);
char	*change_env_virgu(char *s, t_env *env, int *i, char *join_str);
char	*change_env_val(char *s, t_env *env, int *i, char *join_str);

//pipecontrol.c
char	*expand_pipe_redir(t_cmd *cmd);
void	join_with_nl(char *s, int *i, t_quotes *quotes, int *start);
void	count_pipe(t_cmd *cmd, char *s);

//deletequotes.c
char	*ft_deletequotes(char *s);

//redirections.c
int		redirections(t_pipe *pipes);
int		ft_access(char *input);
int		open_file(char *file, char flag);
int		last_redirec(t_redir *redir, int i, int len);

//redir_actions.c
void	action_read(char *type, int fd);
void	action_write(char *type, int fd);
void	action_append(char *type, int fd);
void	action_read_line(t_pipe *pipes, int i);

//env.c
void	init_env(t_env **envi, char **env);
char	*ft_lstfind_env_val(t_env *lst, char *name);
char	**tab_env(t_env *env);
void	env(t_cmd *cmd);

//lst_env.c
t_env	*ft_lstnew(char *name, char *val);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_lstclear(t_env **lst);
void	ft_lstdelone(t_env *lst);
t_env	*ft_lstlast(t_env *lst);

//lst_pipe.c
t_pipe	*ft_newpipe(void);
void	ft_pipeadd_back(t_pipe **lst, t_pipe *new);
t_pipe	*ft_pipelast(t_pipe *pipe);
void	ft_pipedelone(t_pipe *pipe);
void	ft_pipelstclear(t_pipe **lst);

//signal.c
void	ft_suppress_output(int quit);
void	sighandler(int sig);
void	show_readline(void);
void	ft_signal(void);

//signals_heredoc.c
void	ft_signal_heredoc(void);
void	sighandler_heredoc(int sig);

//free_params.c
void	free_split(char **s);
void	free_all(t_cmd *cmd);
void	close_fd(t_redir *redir, int len);
void	close_stdin_stdout(t_cmd *cmd);

//path.c
char	*get_path(char *s, t_env *env);
int		is_builtin(char *s);
void	ft_execve(t_cmd *cmd, t_pipe *pipes);
void	access_execve(t_pipe *pipes, char **char_env, char *p);

//built.c
void	ft_builtin(t_cmd *cmd, t_pipe *pipex);

//pipe.c
void	ft_notpipe(t_cmd *cmd);
void	ft_pipex_child(t_cmd *cmd, t_pipe *pipes);
void	ft_pipex_dad(t_pipe *pipes, pid_t num_pid);
void	ft_pipex(t_cmd *cmd, t_pipe *pipes);

//pipe2.c
void	pipex_main_no_pipe(t_cmd *cmd);
void	pipex_main_with_pipe(t_cmd *cmd);
void	pipex_main(t_cmd *cmd);

//export.c
char	**sort_env(t_env *env);
void	export_no_args(t_cmd *cmd);
void	export_add(t_cmd *cmd, char *val);
void	export(t_cmd *cmd, t_pipe *pipex);

//pwd
void	pwd(void);

//echo
void	echo(t_pipe *pipex);
int		echo_find_n_option(char **str, char *s, int i);
void	print_echo(char **s, int n);

//exit.c
void	ft_exit(t_cmd *cmd);
int		exit_argument(char	**full_cmd, int num);
void	ft_close_exit(t_cmd *cmd);

//unset.c
void	unset(t_cmd *cmd, t_pipe *pipex);
void	delete_env(t_cmd *cmd, t_pipe *pipex, t_env *before, int *i);

//cd.c
void	cd(t_cmd *cmd, t_pipe *pipex);
int		cd_no_argumnets(t_cmd *cmd);
void	cd_up_dir(t_cmd *cmd);
int		cd_undo(t_cmd *cmd);
void	cd_dot_get_pwd(t_cmd *cmd, char **pwd, char **oldpwd);

//cd2.c
void	update_val(t_cmd *cmd, char *name, char *val);
char	*cd_find_full_path(t_cmd *cmd, char *oldpwd);
void	cd_absolute_path(t_cmd *cmd, t_pipe *pipex);
void	cd_relative_path(t_cmd *cmd, t_pipe *pipex);
int		cd_dot_get_path(char *pwd, char **tmp, int i);

//here_doc.c
void	ft_here_doc(t_pipe *pipes, int i);
void	write_pipe(int *fd, t_pipe *pipes, int i);
void	write_pipe_not_last(int *fd, t_pipe *pipes, int i);

#endif
