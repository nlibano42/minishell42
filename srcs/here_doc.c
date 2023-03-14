/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/15 00:23:41 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//#include "../gnl/get_next_line.h"

void ft_here_doc(t_pipe *pipes, int fd)
{
	char *line;

	while(1)
	{
		line = readline("> ");
//		line = get_next_line(fd);
		if (!line)
			return ; // TODO: ctrl+d -> salir sin escribir ni ejecutar nada y sin salto de linea.
		//TODO: ctrl+c -> salir sin escribir ni ejecutar nada y con salto de linea.
		if (!ft_strcmp(line, pipes->redir->key))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}
