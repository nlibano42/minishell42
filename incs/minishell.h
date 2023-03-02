/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:20:30 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/02 23:35:54 by nlibano-         ###   ########.fr       */
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

// # include <stdbool.h>
// # include <stddef.h>
// # include <stdarg.h>
// # include <string.h>
// # include <dirent.h>
// # include <termios.h>

# define READ_END		0  /* index pipe extremo escritura */
# define WRITE_END		1  /* index pipe extremo lectura */

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

//estructura de los comandos. Command + options + arguments
typedef struct s_pipe
{
	char			**full_cmd;
	char			*path;
	int				infile;
	int				outfile;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_redir
{
	char			*key;
	char			*file;
	char			*type; //read, read_l, write, append
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	struct s_env	*env;
	char			**cmd;
	char			*cmd_line;
	char			*readl;
	int				num_pipes;
	struct s_pipe	*pipe;
	struct s_redir	*redir;
}	t_cmd;

typedef struct s_shell
{
	int				quit_status;
	int				pid;
}	t_shell;

t_shell	g_shell;

//main.c
void	save_cmds(t_cmd *cmd);

//init.c
void	init_cmd(t_cmd *cmd);
void	init_quotes_flags(t_quotes *quotes);

//checks.c
void	check_quotes_flags(t_quotes *quotes, char c);
int		is_quotes_opened(char *s);
int		is_two_pipes(char *s);
int		is_open_pipe(char *s);
int		check_init_params(int argc, char **argv);

//checks2.c
int		check_spaces(char *readl);
int		is_fin_redirection(char *s);
int		export_check(char **cmd);
void	ft_control(char *readl, t_quotes *quotes, int i);

//utils.c
char	*find_change_str(char *s, t_env *env);
int		find_str(char c, char *s);
int		find_fin_str(char *s, int i);
int		join_split(t_cmd *cmd);
int		ft_strcmp(char *s1, char *s2);

//error.c
void	access_error(char *input);

//split.c
char	**split(char const *s, char c);
char	**subsplit(char **sp, int start, int len);

//linecontrol.c
int		line_parse(t_cmd *cmd, t_env *envp);
char	*prepare_split(char *readl);
void	expand(char **s, t_env *env);
char	*change_env_val(char *s, t_env *env, int *i, char *join_str);
char	*expand_dolar(char *s, t_env *env, t_quotes *quotes, int *i);

//pipecontrol.c
//char	*expand_pipe_redir(char *cmd);
char	*expand_pipe_redir(t_cmd *cmd);
void	join_with_nl(char *s, int *i, t_quotes *quotes, int *start);
void	count_pipe(t_cmd *cmd, char *s);

//deletequotes.c
char	*ft_deletequotes(char *s);

//redirections.c
void		redirections(char **input);
int			ft_access(char *input);

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
t_pipe	*ft_newpipe();
void	ft_pipeadd_back(t_pipe **lst, t_pipe *new);
t_pipe	*ft_pipelast(t_pipe *pipe);
void	ft_pipedelone(t_pipe *pipe);
void	ft_pipelstclear(t_pipe **lst);

//lst_redir.c
t_redir	*ft_lstnew_redir(void);
void	ft_lstadd_back_redir(t_redir **lst, t_redir *new);
void	ft_lstclear_redir(t_redir **lst);
void	ft_lstdelone_redir(t_redir *lst);
t_redir	*ft_lstlast_redir(t_redir *lst);

//signal.c
void	ft_suppress_output(void);
void	sighandler(int sig);
void	show_readline(void);
void	ft_signal(void);

//free_params.c
void	free_split(char **s);
void	free_all(t_cmd *cmd);

//path.c
char	*get_path(char *s, t_env *env);
int		is_builtin(char *s);
void	ft_execve(t_cmd *cmd);
char	*get_path(char *s, t_env *env);
char	**tab_env(t_env *env);

//built.c
void	ft_builtin(t_cmd *cmd);

//pipe.c
void	pipex_main(t_cmd *cmd);
void	ft_pipex(t_pipe *cmd, t_env *env);

//export.c
char	**sort_env(t_env *env);
void	export_no_args(t_cmd *cmd);
void	export_add(t_cmd *cmd, char *val);
void	export(t_cmd *cmd);

//pwd
void	pwd(t_cmd *cmd);

//echo
void 	echo (t_cmd *cmd);
int		echo_find_n_option(char **str, char *s, int i);
void	print_echo(char **s, int n);

//exit.c
void	ft_exit(t_cmd *cmd);

//unset.c
void	unset(t_cmd *cmd);
void	delete_env(t_cmd *cmd, t_env *env, t_env *before, int *i);

//cd.c
void	cd(t_cmd *cmd);
char	*ft_getcwd(char *cmd);

#endif
