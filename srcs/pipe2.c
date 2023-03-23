/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:25:25 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/23 20:21:03 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	pipex_main_no_pipe(t_cmd *cmd)
{
	if (redirections(cmd->pipe) == 1)
		return ;
	if (is_builtin(cmd->pipe->path))
		ft_builtin(cmd, cmd->pipe);
	else
	{
		g_shell.pid = 1;
		ft_suppress_output(1);
		ft_notpipe(cmd);
		g_shell.pid = 0;
	}
	close_fd(cmd->pipe->redir, cmd->pipe->num_redi);
}

void	pipex_main_with_pipe(t_cmd *cmd)
{
	t_pipe	*pipes;

	pipes = cmd->pipe;
	while (pipes)
	{
		if (pipes->wait == 1)
		{
			pipes = pipes->next;
			continue ;
		}
		ft_pipex(cmd, pipes);
		close_fd(pipes->redir, pipes->num_redi);
		pipes = pipes->next;
	}
	if (cmd->pipe->wait == 1)
	{
		g_shell.pid = 1;
		ft_suppress_output(1);
		ft_notpipe(cmd);
		g_shell.pid = 0;
	}
}

void	pipex_main(t_cmd *cmd)
{
	if (cmd->num_pipes == 0)
		pipex_main_no_pipe(cmd);
	else
		pipex_main_with_pipe(cmd);
}
