/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/07 21:44:41 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*void ft_notpipe(t_cmd *cmd)
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
		ft_execve(cmd, cmd->pipe);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(num_pid, NULL, 0);
	g_shell.pid = 0;
}
*/

void	ft_pipex_child(t_cmd *cmd, t_pipe *pipes)
{
	if (pipes->next)//si no es el ultimo comando
	{
		dup2(pipes->fd[WRITE_END], STDOUT_FILENO);
		close(pipes->fd[WRITE_END]);
	}
	if (pipes->before)//si no es primer comando
	{
		dup2(pipes->before->fd[READ_END], STDIN_FILENO);//Redirige la entrada al descriptor de archivo de la tubería anterior
		close(pipes->fd[READ_END]);// cierra el descriptor de archivo original.
	}
	g_shell.pid = 1;
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
		if (pipes->before)
			close(pipes->before->fd[READ_END]); //cierra el archivo del pipe anterior
	}
}

void	pipex_main(t_cmd *cmd)
{
	t_pipe	*pipes;

	pipes = cmd->pipe;
	while (pipes)
	{
		//redirections(cmd->pipe->full_cmd); // aqui miro si hay alguna redireccion;
		ft_pipex(cmd, pipes); // aqui ejecuto el pipe
		pipes = pipes->next;
	}
/* 	if (cmd->num_pipes == 0)
	{
		if (is_builtin(cmd->pipe->path))
			ft_builtin(cmd, cmd->pipe);
		else
			ft_notpipe(cmd);
	}
	else
	{
		pipes = cmd->pipe;
		while(pipes)
		{
			//redirections(cmd->pipe->full_cmd); // aqui miro si hay alguna redireccion;
			ft_pipex(cmd, pipes); // aqui ejecuto el pipe
			pipes = pipes->next;
		}
	}*/	
}
