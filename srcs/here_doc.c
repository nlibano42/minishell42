/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/21 01:48:18 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	write_pipe_not_last(int *fd, t_pipe *pipes, int i)
{
	char	*line;
	char	*buff;

	(void)fd;
	buff = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(EXIT_SUCCESS); // TODO: ctrl+d -> salir sin escribir ni ejecutar nada y sin salto de linea.
		//TODO: ctrl+c -> salir sin escribir ni ejecutar nada y con salto de linea.
		if (!ft_strcmp(line, pipes->redir[i].key))
		{
			//close(pipes->redir[i].fd);
			free(buff);
			free(line);
			return ;
		}
		buff = ft_strjoin(buff, line);
	}
	free(buff);
}

void	write_pipe(int *fd, t_pipe *pipes, int i)
{
	char	*line;

	close(fd[READ_END]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return ; // TODO: ctrl+d -> salir sin escribir ni ejecutar nada y sin salto de linea.
		//TODO: ctrl+c -> salir sin escribir ni ejecutar nada y con salto de linea.
		if (!ft_strcmp(line, pipes->redir[i].key))
		{
			free(line);
			close(fd[WRITE_END]);
			//close(pipes->redir[i].fd);
			exit(EXIT_SUCCESS);
		}
		write(fd[WRITE_END], line, ft_strlen(line));
		write(fd[WRITE_END], "\n", 1);
		free(line);
	}
}

void	ft_here_doc(t_pipe *pipes, int i)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		pipe_error("Error Pipe", EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		pipe_error("Error Fork", EXIT_FAILURE);
	if (pid == 0)
	{
		g_shell.pid = 1;
//		ft_suppress_output(0);
		write_pipe(fd, pipes, i);
	}
	else
	{
		close(fd[WRITE_END]);
		waitpid(pid, NULL, 0);
		if(WIFEXITED(status))
			g_shell.quit_status = status;
		else if(WIFSIGNALED(status))
			g_shell.quit_status = status + 128;
		g_shell.pid = 0;
	//	ft_suppress_output(1);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
	}
}
