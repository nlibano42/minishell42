/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:03:59 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/19 01:04:12 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	int i;

	ft_putstr_fd("exit\n", 1);
	if (cmd->pipe)
	{	
		i = 0;
		while (cmd->pipe->full_cmd[i])
			i++;
		if(i > 1)
		{
			if (is_digit(cmd->pipe->full_cmd[1]))
			{
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(cmd->pipe->full_cmd[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				g_shell.quit_status = 255;
			}
			else if (i > 2)
			{	
				ft_putstr_fd("bash: exit: too many arguments\n", 2);
				g_shell.quit_status = 1;
			}
			else
				g_shell.quit_status = ft_atoi(cmd->pipe->full_cmd[1]);
		}
		else
			g_shell.quit_status = 0;
	}
	ft_lstclear(&(cmd->env));
	free_all(cmd);
	close(cmd->save_stdin);
	close(cmd->save_stdout);
	//TODO: mirar todo lo que se necesita liberar. 
	exit(g_shell.quit_status);
	//TODO: mirar porque no termina todo. 
	//TODO: CTLR+D apuntar a esta funcion.
}
