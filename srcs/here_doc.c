/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/23 22:00:49 by jdasilva         ###   ########.fr       */
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
			exit(g_shell.quit_status = EXIT_SUCCESS);
		if (!ft_strcmp(line, pipes->redir[i].key))
		{
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
		{
			ft_putstr_fd("\x1b[1A", 1);
			ft_putstr_fd("\033[2C", 1);
			g_shell.quit_status = 15;
			exit(0);
		}
		if (!ft_strcmp(line, pipes->redir[i].key))
		{
			free(line);
			close(fd[WRITE_END]);
			exit(g_shell.quit_status = EXIT_SUCCESS);
		}
		write(fd[WRITE_END], line, ft_strlen(line));
		write(fd[WRITE_END], "\n", 1);
		free(line);
	}
}

void	ft_here_doc_dad(int fd[2], pid_t pid)
{
	int	status;

	close(fd[WRITE_END]);
	waitpid(pid, &status, 0);
	ft_status_heredoc(status);
	g_shell.pid = 0;
	ft_signal();
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}

void	ft_here_doc(t_pipe *pipes, int i)
{
	int		fd[2];
	pid_t	pid;

	ft_signal_heredoc();
	if (pipe(fd) == -1)
		pipe_error("Error Pipe", EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		pipe_error("Error Fork", EXIT_FAILURE);
	if (pid == 0)
	{
		g_shell.pid = 2;
		write_pipe(fd, pipes, i);
		
	}
	else
		ft_here_doc_dad(fd, pid);
}
