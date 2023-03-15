/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/15 18:08:58 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void ft_notpipe(t_cmd *cmd)
{
	pid_t	num_pid;
	
	num_pid = fork();
	if (num_pid < 0)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	else if (num_pid == 0)
	{
		g_shell.pid = 1;
		ft_suppress_output();
		ft_execve(cmd, cmd->pipe);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(num_pid, NULL, 0);
	g_shell.pid = 0;
	ft_suppress_output();
}

void	ft_pipex_child(t_cmd *cmd, t_pipe *pipes)
{
	g_shell.pid = 1;
	ft_suppress_output();
	if (pipes->before)
		dup2(pipes->before->fd[READ_END], STDIN_FILENO);
	if (pipes->next)
	{
		dup2(pipes->fd[WRITE_END], STDOUT_FILENO);
		close(pipes->fd[WRITE_END]);
	}
	if (redirections(pipes) == 1)
		return ;
	ft_execve(cmd, pipes);
	free_all(cmd);
	exit(EXIT_FAILURE);
}

void	ft_pipex(t_cmd *cmd, t_pipe *pipes)
{
	pid_t	num_pid;

	if (pipe(pipes->fd) == -1)
		pipe_error("Error Pipe", EXIT_FAILURE);
	num_pid = fork();
	if (num_pid < 0)
		pipe_error("Error Fork", EXIT_FAILURE);
	else if (num_pid == 0)
		ft_pipex_child(cmd, pipes);
	else
	{
		close(pipes->fd[WRITE_END]);
		waitpid(num_pid, NULL, 0);
		g_shell.pid = 0;
		ft_suppress_output();
		if (pipes->before)
			close(pipes->before->fd[READ_END]);
		if (!pipes->next)
			close(pipes->fd[READ_END]);
	}
}

void	close_fd(t_redir *redir, int len)
{
	int		i;

	i = -1;
	while (++i < len)
	{	
		if (redir[i].fd > -1)
			close(redir[i].fd);
	}
}

void	pipex_main(t_cmd *cmd)
{
	t_pipe	*pipes;

 	if (cmd->num_pipes == 0)
	{
		if (redirections(cmd->pipe) == 1)
			return ;
		if (is_builtin(cmd->pipe->path))
			ft_builtin(cmd, cmd->pipe);
		else
			ft_notpipe(cmd);
		close_fd(cmd->pipe->redir, cmd->pipe->num_redi);
	}
	else
	{
		pipes = cmd->pipe;
		while(pipes)
		{
/* 			if (redirections(pipes) == 1)
				return ; */
			ft_pipex(cmd, pipes);
			close_fd(pipes->redir, pipes->num_redi);
			pipes = pipes->next;
		}
	}
}
