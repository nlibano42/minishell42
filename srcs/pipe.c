/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/23 20:52:30 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void ft_pipex(t_pipe *cmd, t_env *env)
{
	int fd[2];

	if(pipe(fd) == -1)
		perror("Error Pipe"); //podemos hacer la funcion para que salga del programa con el exit. 
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


void pipex_main(t_cmd *cmd)
{

	while(cmd->pipe)
	{
		redirections(cmd->pipe->full_cmd); // aqui miro si hay alguna redireccion;
		ft_pipex(cmd->pipe, cmd->env); // aqui ejecuto el pipe
		cmd->pipe = cmd->pipe->next;
	}
}