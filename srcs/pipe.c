/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/06 21:18:41 by jdasilva         ###   ########.fr       */
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
		ft_execve(cmd);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(num_pid, NULL, 0);
	g_shell.pid = 0;
}

void	ft_pipex(t_cmd *cmd)
{
	pid_t num_pid;

	if(pipe(cmd->pipe->fd) == -1)
	{
		perror("Error Pipe");
		exit(EXIT_FAILURE);
	}
	num_pid = fork();
	if (num_pid < 0)
	{
		perror("Error Fork");
		exit (EXIT_FAILURE);
	}
	else if (num_pid == 0)
	{
		//printf("Entra:%s\n", cmd->pipe->path);
		if(cmd->pipe->before)//si no es primer comando
		{
			//printf("HIJO:\nbefore:%s === %s\n" , cmd->pipe->before->path, cmd->pipe->path);
			dup2(cmd->pipe->fd[READ_END], STDIN_FILENO);//Redirige la entrada al descriptor de archivo de la tubería anterior
			close(cmd->pipe->fd[READ_END]);// cierra el descriptor de archivo original.
		}
		if(cmd->pipe->next)//si no es el ultimo comando
		{
			//printf("HIJO:\nnext:%s === %s\n" , cmd->pipe->next->path, cmd->pipe->path);
			dup2(cmd->pipe->fd[WRITE_END], STDOUT_FILENO);
			close(cmd->pipe->fd[WRITE_END]);
		}
		g_shell.pid = 1;
		ft_execve(cmd);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
  		if(cmd->pipe->before)
		{	
			//printf("PADRE:\nbefore:%s === %s\n" , cmd->pipe->before->path, cmd->pipe->path);
			close(cmd->pipe->before->fd[READ_END]); //cierra el archivo del pipe anterior
		}
		if(cmd->pipe->next)
		{
			//printf("PADRE:\nnext:%s === %s\n" , cmd->pipe->next->path, cmd->pipe->path);
			cmd->pipe->next->fd[READ_END] = cmd->pipe->fd[READ_END];//guarda el descriptor de archivo de la tubería actual para la siguiente iteración
			close(cmd->pipe->fd[WRITE_END]);
		}
		waitpid(num_pid, NULL, 0);
		g_shell.pid = 0;	
	} 
}

void	pipex_main(t_cmd *cmd)
{

	if (cmd->num_pipes == 0)
	{
		if (is_builtin(cmd->pipe->path))
			ft_builtin(cmd);
		else
			ft_notpipe(cmd);
	}
	else
	{
	 	while(cmd->pipe)
		{
			//redirections(cmd->pipe->full_cmd); // aqui miro si hay alguna redireccion;
			ft_pipex(cmd); // aqui ejecuto el pipe
			cmd->pipe = cmd->pipe->next;
		} 
	}		
}
