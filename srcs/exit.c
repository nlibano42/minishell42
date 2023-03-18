/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:03:59 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/18 21:16:26 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	int size;
	int i;

	ft_putstr_fd("exit\n", 1);
	i= -1;
	size= 0;
	while (cmd->pipe->full_cmd[++i])
		size++;
	if(size > 1)
	{

		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		//funcion para borrar todo.
		exit(1);
	}
	ft_lstclear(&(cmd->env));
	free_all(cmd);
	close(cmd->save_stdin);
	close(cmd->save_stdout);
	//TODO: mirar todo lo que se necesita liberar. 
	exit(0);
	//TODO: mirar porque no termina todo. 
	//TODO: CTLR+D apuntar a esta funcion.
}
