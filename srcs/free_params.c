/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 22:05:45 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/24 15:52:52 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_split(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	free_all(t_cmd *cmd)
{
	if (cmd->cmd)
	{
		free_split(cmd->cmd);
		cmd->cmd = NULL;
	}
	if (cmd->cmd_line)
	{
		free(cmd->cmd_line);
		cmd->cmd_line = NULL;
	}
	if (cmd->readl)
	{
		free(cmd->readl);
		cmd->readl = NULL;
	}
	if (cmd->pipe)
	{
		ft_pipelstclear(&(cmd->pipe));
		cmd->pipe = NULL;
	}
}

void	close_fd(t_redir *redir, int len)
{
	int		i;

	i = -1;
	while (++i < len)
	{	
		if (redir[i].fd > -1)
			close(redir[i].fd);
	}
}

void	close_stdin_stdout(t_cmd *cmd)
{
	dup2(cmd->save_stdin, STDIN_FILENO);
	dup2(cmd->save_stdout, STDOUT_FILENO);
	close(cmd->save_stdin);
	close(cmd->save_stdout);
}
