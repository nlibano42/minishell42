/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 01:54:26 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/01 17:43:43 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	unset(t_cmd *cmd)
{
	t_env	*env;
	t_env	*before;
	int		i;

	if (!cmd->pipe->full_cmd[1])
		return ;
	i = 0;
	while (cmd->pipe->full_cmd[++i])
	{	
		before = NULL;
		env = cmd->env;
		while (env)
		{
			if (ft_strcmp(env->name, cmd->pipe->full_cmd[i]) == 0)
			{
				if (before)
				{
					if(!env->next)
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
				return ;
			}
			before = env;
			env = env->next;
		}
	}
	return ;
}