/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:54:10 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/22 20:36:30 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	action_read(char *type, int fd)
{
	if (!ft_strcmp(type, "read"))
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	action_write(char *type, int fd)
{
	if (!ft_strcmp(type, "write"))
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	action_append(char *type, int fd)
{
	if (!ft_strcmp(type, "append"))
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	action_read_line(t_pipe *pipes, int i)
{
	if (!ft_strcmp(pipes->redir[i].type, "readl"))
	{
		dup2(pipes->redir[i].fd, STDIN_FILENO);
		if (last_redirec(pipes->redir, i, pipes->num_redi) == 1)
			write_pipe_not_last(pipes->fd, pipes, i);
		else
			ft_here_doc(pipes, i);
	}
}
