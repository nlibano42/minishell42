/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:07:27 by nlibano-          #+#    #+#             */
/*   Updated: 2022/12/15 04:07:31 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct  s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct	s_shell
{
	struct s_env	*env;
	int				quit_status;
	int				pid;
	char			*readl;
} t_shell;

t_shell g_shell;

//main.c
int main(int argc, char **argv, char **env);

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

#endif