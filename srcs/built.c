/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:26:13 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/07 22:03:02 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_builtin(t_cmd *cmd, t_pipe *pipex)
{
	if (ft_strcmp(pipex->path, "export") == 0)
		export(cmd, pipex);
	else if (ft_strcmp(pipex->path, "pwd") == 0)
		pwd(cmd);
	else if (ft_strcmp(pipex->path, "env") == 0)
		env(cmd);
	else if (ft_strcmp(pipex->path, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(pipex->path, "cd") == 0)
		cd(cmd, pipex);
	else if (ft_strcmp(pipex->path, "echo") == 0)
		echo(pipex);
	else if (ft_strcmp(pipex->path, "unset") == 0)
		unset(cmd, pipex);
}
