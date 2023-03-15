/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/15 17:26:10 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//#include "../gnl/get_next_line.h"

void ft_here_doc(t_pipe *pipes, int fd)
{
	char	*line;
	char	*buffer;

	buffer = ft_strdup("");
	while(1)
	{
		line = readline("> ");
//		line = get_next_line(fd);
		if (!line)
			return ; // TODO: ctrl+d -> salir sin escribir ni ejecutar nada y sin salto de linea.
		//TODO: ctrl+c -> salir sin escribir ni ejecutar nada y con salto de linea.
		if (!ft_strcmp(line, pipes->redir->key))
			break ;
		buffer = ft_strjoin(buffer, line);
		buffer = ft_strjoin(buffer, ft_strdup("\n"));
	}
	write(fd, buffer, ft_strlen(buffer));
	free(line);
}
