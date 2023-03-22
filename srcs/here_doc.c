/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:29:26 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/22 19:13:34 by nlibano-         ###   ########.fr       */
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
			exit(EXIT_SUCCESS);
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
			exit(g_shell.quit_status = 0);
		}
		if (!ft_strcmp(line, pipes->redir[i].key))
		{
			free(line);
			close(fd[WRITE_END]);
			exit(EXIT_SUCCESS);
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
	if (WIFEXITED(status))
		g_shell.quit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_shell.quit_status = WTERMSIG(status) + 128;
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
