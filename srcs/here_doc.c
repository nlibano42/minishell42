/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/15 17:45:38 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//#include "../gnl/get_next_line.h"

void ft_here_doc(t_pipe *pipes, int fd[2])
{
	char	*line;
//	char	*buffer;

//	buffer = ft_strdup("");
	while(1)
	{
		line = readline("> ");
		if (!line)
			return ; // TODO: ctrl+d -> salir sin escribir ni ejecutar nada y sin salto de linea.
		//TODO: ctrl+c -> salir sin escribir ni ejecutar nada y con salto de linea.
		if (!ft_strcmp(line, pipes->redir->key))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
//		buffer = ft_strjoin(buffer, line);
//		buffer = ft_strjoin(buffer, ft_strdup("\n"));
	}
//	write(fd, buffer, ft_strlen(buffer));
	free(line);
}
