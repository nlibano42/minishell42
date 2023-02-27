/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:36:21 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/28 00:33:15 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**sort_env(t_env *env)
{
	char	**sort;
	char	*tmp;
	int		i;
	int		j;

	sort = tab_env(env);
	i = -1;
	while (sort[++i])
	{
		j = -1;
		while (sort[++j])
		{
			if (ft_strcmp(sort[i], sort[j]) < 0)
			{
				tmp = sort[i];
				sort[i] = sort[j];
				sort[j] = tmp;
			}
		}
	}
	return (sort);
}

void	export_no_args(t_cmd *cmd)
{
	int		i;
	char	**sort;
	char	**split;

	sort = sort_env(cmd->env);
	i = -1;
	while (sort[++i])
	{
		split = ft_split(sort[i], '=');
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(split[0], 1);
		if (split[1])
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(split[1], 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		free_split(split);
	}
	free_split(sort);
}

void	export_add(t_cmd *cmd, char *val)
{
	t_env	*new;
	char	**sp;

	sp = ft_split(val, '=');
	if (!sp[1])
		new = ft_lstnew(sp[0], "");
	else
		new = ft_lstnew(sp[0], sp[1]);
	ft_lstadd_back(&(cmd->env), new);
	free_split(sp);
}

void	export(t_cmd *cmd)
{
	int		exist;
	char	**val;
	t_env	*env;
	int		i;

	if (!cmd->pipe->full_cmd[1])
	{
		export_no_args(cmd);
		return ;
	}
	if (export_check(cmd->pipe->full_cmd))
		return ;
	i = 0;
	while (cmd->pipe->full_cmd[++i])
	{
		val = ft_split(cmd->pipe->full_cmd[i], '=');
		exist = 0;
		env = cmd->env;
		while (env)
		{
			if (ft_strcmp(env->name, val[0]) == 0)
			{
				free(env->val);
				if (!val[1])
					env->val = ft_strdup("");
				else
					env->val = ft_strdup(val[1]);
				exist = 1;
				break ;
			}
			env = env->next;
		}
		if (exist == 0)
			export_add(cmd, cmd->pipe->full_cmd[i]);
		free_split(val);
	}
}
