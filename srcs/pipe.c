/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/24 19:59:44 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


void ft_notpipe(t_pipe *pipe, t_env *env)
{
	g_shell.pid = fork();
	if(g_shell.pid < 0)
		perror("fork");
	else if(g_shell.pid == 0)
	{
		ft_execve(pipe, env);
		perror("execve");
		exit(1);
	}
	else
		waitpid(g_shell.pid, NULL, 0);
	
}
void	ft_pipex(t_pipe *cmd, t_env *env)
{
	int fd[2];
	 
	g_shell.pid = fork();
	if(g_shell.pid == 0)
	{
		close(fd[READ_END]);
		if(dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
			perror("error");
		close(fd[WRITE_END]);
		ft_execve(cmd, env);
	}
	else
	{
		close(fd[WRITE_END]);
		if(dup2(fd[READ_END], STDIN_FILENO) == -1)
			perror("error");
		close(fd[READ_END]);
		waitpid(g_shell.pid, NULL, 0);
	}
}

void	pipex_main(t_cmd *cmd)
{
	if (cmd->num_pipes == 0)
		ft_notpipe(cmd->pipe, cmd->env);
	else
	{
	 	while(cmd->pipe)
		{
			//redirections(cmd->pipe->full_cmd); // aqui miro si hay alguna redireccion;
			ft_pipex(cmd->pipe, cmd->env); // aqui ejecuto el pipe
			cmd->pipe = cmd->pipe->next;
		} 
	}		
}