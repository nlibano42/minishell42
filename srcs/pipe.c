/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/25 18:25:18 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_notpipe(t_cmd *cmd)
{
	pid_t	num_pid;
	int		status;

	num_pid = fork();
	if (num_pid < 0)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	else if (num_pid == 0)
	{
		g_shell.pid = 1;
		ft_suppress_output(1);
		ft_execve(cmd, cmd->pipe);
		free_all(cmd);
		exit(g_shell.quit_status = EXIT_FAILURE);
	}
	waitpid(num_pid, &status, 0);
	ft_status(status);
	g_shell.pid = 0;
	ft_suppress_output(0);
}

void	ft_pipex_child_before(t_pipe *pipes)
{
	if (pipes->before->redir && \
			!ft_strcmp(pipes->before->redir->type, "readl"))
		dup2(pipes->fd[READ_END], STDIN_FILENO);
	else
	{
		if (pipes->redir && !ft_strcmp(pipes->redir->type, "readl"))
			redirections(pipes);
		else
			dup2(pipes->before->fd[READ_END], STDIN_FILENO);
	}
}

void	ft_pipex_child(t_cmd *cmd, t_pipe *pipes)
{
	g_shell.pid = 1;
	ft_suppress_output(1);
	if (pipes->before)
		ft_pipex_child_before(pipes);
	if (pipes->next)
	{
		if (pipes->redir && !ft_strcmp(pipes->redir->type, "readl"))
			redirections(pipes);
		else
		{
			dup2(pipes->fd[WRITE_END], STDOUT_FILENO);
			close(pipes->fd[WRITE_END]);
		}
	}
	if (pipes->redir && ft_strcmp(pipes->redir->type, "readl"))
	{
		if (redirections(pipes) == 1)
			return ;
	}
	ft_execve(cmd, pipes);
	free_all(cmd);
	exit(g_shell.quit_status = EXIT_FAILURE);
}

void	ft_pipex_dad(t_pipe *pipes, pid_t num_pid)
{
	int		status;

	close(pipes->fd[WRITE_END]);
	if (pipes->before)
		close(pipes->before->fd[READ_END]);
	if (!pipes->next)
		close(pipes->fd[READ_END]);
	waitpid(num_pid, &status, 0);
	ft_status(status);
	g_shell.pid = 0;
	ft_suppress_output(0);
}

void	ft_pipex(t_cmd *cmd, t_pipe *pipes)
{
	pid_t	num_pid;

	if (pipe(pipes->fd) == -1)
		pipe_error("Error Pipe", EXIT_FAILURE);
	num_pid = fork();
	ft_suppress_output(1);
	if (num_pid < 0)
		pipe_error("Error Fork", EXIT_FAILURE);
	else if (num_pid == 0)
		ft_pipex_child(cmd, pipes);
	else
		ft_pipex_dad(pipes, num_pid);
}
