/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/15 19:27:02 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//#include "../gnl/get_next_line.h"

void	write_pipe(int *fd, t_pipe *pipes)
{
	char *line;

	while(1)
	{
		line = readline("> ");
		if (!line)
			return ; // TODO: ctrl+d -> salir sin escribir ni ejecutar nada y sin salto de linea.
		//TODO: ctrl+c -> salir sin escribir ni ejecutar nada y con salto de linea.
		if (!ft_strcmp(line, pipes->redir->key))
			break ;
		write(fd[WRITE_END], line, ft_strlen(line));
		write(fd[WRITE_END], "\n", 1);
		free(line);
//		buffer = ft_strjoin(buffer, line);
//		buffer = ft_strjoin(buffer, ft_strdup("\n"));
	}
	free(line);
//	write(fd, buffer, ft_strlen(buffer));
}


void ft_here_doc(t_pipe *pipes)
{
	int fd[2];
	pid_t pid;
	
	if(pipe(fd) == -1)
		pipe_error("Error Pipe", EXIT_FAILURE);
	pid = fork();
	if(pid < 0)
		pipe_error("Error Fork", EXIT_FAILURE);
	if(pid == 0)
	{
		g_shell.pid = 1;
//		ft_suppress_output(0);
		write_pipe(fd, pipes);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	g_shell.pid = 0;
//	ft_suppress_output(1);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	
}
