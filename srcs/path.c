/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:51:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/16 18:16:44 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_execve(t_cmd *cmd, t_pipe *pipes)
{
	char	**char_env;
	char	*p;

	char_env = tab_env(cmd->env);
	p = pipes->path;
	if (is_builtin(pipes->path))
		ft_builtin(cmd, pipes);
	else
	{
		if (pipes->redir && !ft_strcmp(pipes->redir->type, "readl"))
		{
			if(p == NULL)
				return;
		}
		if(p !=  NULL)
		{
			if (ft_strlen(p) == 0)
			{
				free_split(char_env);
				return ;
			}
			execve(p, pipes->full_cmd, char_env);
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ft_deletequotes(pipes->full_cmd[0]), 2);
		ft_putstr_fd(": command not found\n", 2);
		g_shell.quit_status = 127;
		free_split(char_env);
	}
}

int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || \
			!ft_strcmp(s, "pwd") || !ft_strcmp(s, "export") || \
			!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") || \
			!ft_strcmp(s, "exit"))
		return (1);
	else
		return (0);
}

char	*get_path(char *s, t_env *env)
{
	char	*path;
	char	**sp;
	int		i;

	if(!s)
		return(NULL);
	s = ft_deletequotes(s);
	if (is_builtin(s))
	{
		free(s);
		return (ft_strdup(s));
	}
	else
	{
		path = ft_lstfind_env_val(env, "PATH");
		sp = ft_split(path, ':');
		i = -1;
		while (sp[++i])
		{
			path = ft_strjoin(ft_strdup(sp[i]), ft_strdup("/"));
			path = ft_strjoin(path, ft_strdup(s));
			if (access(path, F_OK) == 0)
			{
				free_split(sp);
				free(s);
				return (path);
			}
		}
		free_split(sp);
		free(s);
	}
	return (NULL);
}
