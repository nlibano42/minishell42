/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:26:13 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/28 22:12:14 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_builtin(t_cmd *cmd)
{
//	printf("Aqui va los builtin\n");
	if (ft_strcmp(cmd->pipe->path, "export") == 0)
		export(cmd);
	else if (ft_strcmp(cmd->pipe->path, "pwd") == 0)
		pwd(cmd);
	else if (ft_strcmp(cmd->pipe->path, "env") == 0)
		env(cmd);
	else if (ft_strcmp(cmd->pipe->path, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd->pipe->path, "cd") == 0)
		cd(cmd);
 	else if (ft_strcmp(cmd->pipe->path, "echo") == 0)
		echo(cmd);
}