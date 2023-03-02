/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:51:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/03 00:57:09 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_execve(t_cmd *cmd)
{
	char	**char_env;
	char	*p;

	char_env = tab_env(cmd->env);
	p = cmd->pipe->path;
	if (is_builtin(cmd->pipe->path))
		ft_builtin(cmd);
	else
		execve(p, cmd->pipe->full_cmd, char_env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(ft_deletequotes(cmd->pipe->full_cmd[0]), 2);
	ft_putstr_fd(": command not found\n", 2);
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
	//TODO: para recortar lineas en la funcion get_path.
}

char	*get_path(char *s, t_env *env)
{
	char	*path;
	char	**sp;
	int		i;

	ft_deletequotes(s); //TODO: aqui tampoco hace nada.
	if (is_builtin(s))
		return (ft_strdup(s));
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
				return (path);
			}
		}
		free_split(sp);
	}
	return (NULL);
}
