/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:51:38 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/03 00:50:20 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	pwd(t_cmd *cmd)
{
	t_env	*env;

	env = cmd->env;
	while (env)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
		{
			ft_putstr_fd(env->val, 1);
			ft_putstr_fd("\n", 1);
			break ;
		}
		env = env->next;
	}
}
