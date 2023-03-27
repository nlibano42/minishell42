/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:51:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/27 16:57:20 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	access_execve(t_pipe *pipes, char **char_env, char *p)
{
	if (pipes->redir && !ft_strcmp(pipes->redir->type, "readl"))
		if (p == NULL)
			return ;
	if (p != NULL)
	{
		if (ft_strlen(p) == 0)
		{
			free_split(char_env);
			return ;
		}
		execve(p, pipes->full_cmd, char_env);
	}
}

void	ft_execve(t_cmd *cmd, t_pipe *pipes)
{
	char	**char_env;
	char	*p;
	char	*print_cmd;

	if (!pipes->full_cmd[0])
		exit(g_shell.quit_status = 0);
	print_cmd = ft_deletequotes(pipes->full_cmd[0]);
	char_env = tab_env(cmd->env);
	p = pipes->path;
	if (is_builtin(pipes->path))
		ft_builtin(cmd, pipes);
	else
	{
		access_execve(pipes, char_env, p);
		execve_error(print_cmd);
		free(print_cmd);
		free_split(char_env);
		exit(g_shell.quit_status = EXIT_FAILURE);
	}
	free(print_cmd);
	free_split(char_env);
}

int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || \
			!ft_strcmp(s, "pwd") || !ft_strcmp(s, "export") || \
			!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") || \
			!ft_strcmp(s, "exit"))
		return (g_shell.quit_status = 0, 1);
	else
		return (0);
}

char	*get_findpath(char *str, t_env *env)
{
	char	*path;
	char	**sp;
	int		i;

	path = ft_lstfind_env_val(env, "PATH");
	if (path)
	{
		sp = ft_split(path, ':');
		i = -1;
		while (sp[++i])
		{
			path = ft_strjoin(ft_strdup(sp[i]), ft_strdup("/"));
			path = ft_strjoin(path, ft_deletequotes(str));
			if (access(path, F_OK) == 0)
			{
				free_split(sp);
				return (path);
			}
			free(path);
		}
		free_split(sp);
	}
	return (NULL);
}

char	*get_path(char *str, t_env *env)
{
	char	*s;

	if (!str)
		return (NULL);
	s = ft_deletequotes(str);
	if (!ft_strncmp(s, "./", 2) || !ft_strncmp(s, "/", 1))
	{
		free(s);
		return (ft_deletequotes(str));
	}
	if (is_builtin(s))
		return (s);
	else
	{
		free(s);
		return (get_findpath(str, env));
	}
	free(s);
	return (NULL);
}
