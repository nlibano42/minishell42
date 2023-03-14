/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/14 19:58:50 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void ft_here_doc(t_pipe *pipes)
{
	char *line;

	while(1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, pipes->redir->key))
			break ;
		write(pipes->redir->fd, line, ft_strlen(line));
		write(pipes->redir->fd, "\n", 1);
		free(line);
	}
	free(line);
	dup2(pipes->redir->fd, STDIN_FILENO);
	close(pipes->redir->fd);
}
