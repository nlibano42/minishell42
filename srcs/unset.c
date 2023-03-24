/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:54:26 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/23 00:33:02 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	sub_delete_env(t_cmd *cmd, t_env *before, t_env *env)
{
	if (before)
	{
		if (!env->next)
			before->next = NULL;
		else
			before->next = env->next;
		ft_lstdelone(env);
	}
	else
	{
		before = env;
		cmd->env = cmd->env->next;
		ft_lstdelone(before);
	}
}

void	delete_env(t_cmd *cmd, t_pipe *pipex, t_env *before, int *i)
{
	t_env	*env;
	char	*name;

	name = ft_deletequotes(pipex->full_cmd[*i]);
	if (export_check(ft_strdup(name)) == 0)
	{
		env = cmd->env;
		while (env)
		{
			if (ft_strcmp(env->name, name) == 0)
			{
				sub_delete_env(cmd, before, env);
				free(name);
				return ;
			}
		before = env;
		env = env->next;
		}
		free(name);
	}	
}

void	unset(t_cmd *cmd, t_pipe *pipex)
{
	t_env	*before;
	int		i;

	if (!cmd->pipe->full_cmd[1])
		return ;
	i = 0;
	while (cmd->pipe->full_cmd[++i])
	{	
		before = NULL;
		delete_env(cmd, pipex, before, &i);
	}
	return ;
}
