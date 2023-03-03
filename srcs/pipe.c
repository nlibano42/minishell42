/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/03 18:39:22 by jdasilva         ###   ########.fr       */
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
		ft_signal();
		ft_execve(cmd);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	waitpid(num_pid, NULL, 0);
	g_shell.pid = 0;
}

/* void	ft_pipex(t_cmd *cmd, t_env *env)
{
	pid_t num_pid;

		num_pid = fork();
	if (num_pid < 0)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	else if (num_pid == 0)
	{
		if(cmd->pipe->before)//si no es primer comando
		{
			dup2(cmd->pipe->fd[0], STDIN_FILENO);//Redirige la entrada al descriptor de archivo de la tubería anterior
			close(cmd->pipe->fd[0]);// cierra el descriptor de archivo original.
		}
		if(cmd->pipe->next)//si no es el ultimo comando
		{
			dup2(cmd->pipe->fd[1], STDOUT_FILENO);
			close(cmd->pipe->fd[1]);
		}
		g_shell.pid = 1;
		ft_signal();
		ft_execve(cmd);
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(num_pid, NULL, 0);
		if(cmd->pipe->before)
			close(cmd->pipe->before->fd[0]); //cierra el archivo del pipe anterior
		if(cmd->pipe->next)
		{
			cmd->pipe->next->fd[0] = cmd->pipe->fd[0];//guarda el descriptor de archivo de la tubería actual para la siguiente iteración
			close(cmd->pipe->fd[1]);
		}
	}
	
	
} */
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
			//ft_pipex(cmd, cmd->env); // aqui ejecuto el pipe
			cmd->pipe = cmd->pipe->next;
		} 
	}		
}