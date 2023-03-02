/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:09:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/02 20:02:38 by jdasilva         ###   ########.fr       */
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

void	ft_pipex(t_cmd *cmd, t_env *env)
{

}

void	pipex_main(t_cmd *cmd)
{
	int	i;
	
	if (cmd->num_pipes == 0)
	{
		if (is_builtin(cmd->pipe->path))
			ft_builtin(cmd);
		else
			ft_notpipe(cmd);
	}
	else
	{
		cmd->fdpipes =(int **)malloc(cmd->num_pipes * sizeof(int *));
		i = -1;
		while(++i <= cmd->num_pipes) // El propósito de crear una tubería 
		//para cada comando es permitir la comunicación entre los diferentes comandos en la línea de entrada.
		{
			cmd->fdpipes[i] =(int **)malloc( 2 * sizeof(int));
			if(pipe(cmd->fdpipes[i]) == - 1)
			{
				perror("fdpipe");
				exit(EXIT_FAILURE);
			}
		} // se puede llevar esto con la struc pipes, mirando un anterior para  conectar los fd.
	 	while(cmd->pipe)
		{
			//redirections(cmd->pipe->full_cmd); // aqui miro si hay alguna redireccion;
			ft_pipex(cmd, cmd->env); // aqui ejecuto el pipe
			cmd->pipe = cmd->pipe->next;
		} 
	}		
}