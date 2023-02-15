/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:07:27 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/15 15:20:30 by nlibano-         ###   ########.fr       */
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

//# include <stdbool.h>
//# include <stdlib.h>
// # include <stddef.h>
// # include <stdarg.h>
// # include <string.h>
// # include <dirent.h>
// # include <sys/wait.h>
// # include <errno.h>
// # include <termios.h>

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
	char	*cmd;
	char	*opt;
	char	*args;
}	t_pipe;

typedef struct s_cmd
{
	struct s_env	*env;
	char			**cmd;	
	char			*cmd_line;
	char			*readl;
	int				num_pipes;
	struct s_pipe	pipe;
}	t_cmd;

typedef struct s_shell
{
	int				quit_status;
	int				pid;
}	t_shell;

t_shell	g_shell;

//main.c
void	init_cmd(t_cmd *cmd);
void	ft_signal(void);

//utils.c
char	*find_change_str(char *s, t_env *env);
int		find_str(char c, char *s);
char	*ft_join_str(char *s1, char *s2);
int		find_fin_str(char *s, int i);

//linecontrol.c
int		linecontrol(t_cmd *cmd, t_env *envp);
char	*ft_controlcomillas(char *readl);
void	expand(char **s, t_env *env);
void	ft_control(char *readl, int *s_f, int *d_f, int i);
char	*ft_parching_dolar(char *s, t_env *env, int i, char *join_str);
//char	*ft_control_expand(char **s, t_env *env, char *join_str, int *i);
char	*ft_control_expand(char *s, t_env *env, t_quotes *quotes, int *i);
int		join_split(t_cmd *cmd);

//pipecontrol.c
char	*ft_pipecontrol(char *cmd);
void	ft_quotes_crontol(char *s, t_quotes *quotes, int *i);

//deletequotes.c
char	*ft_deletequotes(char *s);

//redirections.c
void	redirections(char *s);

//env.c
void	init_env(t_env **envi, char **env);
char	*ft_lstfind_env_val(t_env *lst, char *name);

//lst_env.c
t_env	*ft_lstnew(char *name, char *val);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_lstclear(t_env **lst);
void	ft_lstdelone(t_env *lst);
t_env	*ft_lstlast(t_env *lst);

//signal.c
void	ft_suppress_output(void);
void	sighandler(int sig);
void	show_readline(void);

//free_params.c
void	free_split(char **s);

#endif
