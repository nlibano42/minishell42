/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:03:59 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/16 18:44:45 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	ft_lstclear(&(cmd->env));
	free_all(cmd);
	//TODO: mirar todo lo que se necesita liberar. 
	ft_putstr_fd("exit\n", 1);
	exit(0);
	//TODO: mirar porque no termina todo. 
	//TODO: CTLR+D apuntar a esta funcion.
}
