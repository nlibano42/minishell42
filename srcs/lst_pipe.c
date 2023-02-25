/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:38:36 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/25 18:55:19 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_pipe	*ft_newpipe(void)
{
	t_pipe *pipe;
	
	pipe = malloc(sizeof(t_pipe));
	if(!pipe)
		return (NULL);
	pipe->full_cmd = NULL;
	pipe->path = NULL;
	pipe->infile = 0;
	pipe->outfile = 0;
	pipe->next = NULL;
	return(pipe);
}

void	ft_pipeadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*last_lst;

	if (!*lst)
		*lst = new;
	else
	{
		last_lst = ft_pipelast(*lst);
		last_lst->next = new;
	}
}

t_pipe *ft_pipelast(t_pipe *pipe)
{
	while(pipe)
	{
		if(!(pipe->next))
			return(pipe);
		pipe = pipe->next;
	}
	return(pipe);
}



void ft_pipedelone(t_pipe *pipe)
{
	if(pipe)
	{
		free_split(pipe->full_cmd); // creo que al ser ** se tiene que liberar ambos no(?¿)
		free(pipe->path);
		free(pipe);
	}
}

void	ft_pipelstclear(t_pipe **lst)
{
	t_pipe	*begin;

	if (lst)
	{
		while (*lst)
		{
			begin = (*lst)->next;
			ft_pipedelone(*lst);
			*lst = begin;
		}
	}
}
