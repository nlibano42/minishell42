/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:26:13 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/22 14:50:13 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_builtin(t_cmd *cmd, t_pipe *pipex)
{
	if (ft_strcmp(pipex->path, "export") == 0)
		export(cmd, pipex);
	else if (ft_strcmp(pipex->path, "pwd") == 0)
		pwd();
	else if (ft_strcmp(pipex->path, "env") == 0)
	{
		if (!pipex->full_cmd[1])
			env(cmd);
		else
		{
			ft_putstr_fd("Minishell: Too many argumets\n", 2);
			return ;
		}
	}
	else if (ft_strcmp(pipex->path, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(pipex->path, "cd") == 0)
		cd(cmd, pipex);
	else if (ft_strcmp(pipex->path, "echo") == 0)
		echo(pipex);
	else if (ft_strcmp(pipex->path, "unset") == 0)
		unset(cmd, pipex);
}
