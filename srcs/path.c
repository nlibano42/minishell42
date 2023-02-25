/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:51:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/25 19:41:43 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**tab_env(t_env *env)
{
	char **tab;
	int	i;
	char *s;

	i = 1;
	while(env)
	{
		i++;
		env = env->next;
	}
	tab = (char **)malloc((sizeof(char *) * i + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while(env)
	{
		s = ft_strjoin(ft_strdup(env->name), ft_strdup("="));
		s = ft_strjoin(s, ft_strdup(env->val));
		tab[++i] = s;
		env = env->next;
	}
	tab[i + 1] = NULL;
	return (tab);
}

void	ft_execve(t_pipe *pipe, t_env *env)
{
	char	**char_env;
	char	*p;

	char_env = tab_env(env);
	p = pipe->path;
	if (is_builtin(p))
		ft_builtin(p);
	else
	{
		execve(p, pipe->full_cmd, char_env);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*pipe->full_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo")|| !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd") || \
	!ft_strcmp(s, "export") || !ft_strcmp(s, "unset") || \
	!ft_strcmp(s, "env") || !ft_strcmp(s, "exit"))
		return(1);
	else
		return(0);
	//para recortar lineas en la funcion get_path.
}
char	*get_path(char *s, t_env *env)
{
	char	*path;
	char	**sp;
	int		i;

	if (is_builtin(s))
		return (s);
	else
	{
		path = ft_lstfind_env_val(env, "PATH");
		sp = ft_split(path, ':');
		i = -1;
		while(sp[++i])
		{
			path = ft_strjoin(ft_strdup(sp[i]), ft_strdup("/"));
			path = ft_strjoin(path, ft_strdup(s));
	 		if(access(path, F_OK) == 0)
			{
				free_split(sp);
				return (path);
			}
		}
		free_split(sp);
	}
	return (NULL);
}