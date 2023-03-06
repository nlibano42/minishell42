/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:41:00 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/06 17:05:56 by jdasilva         ###   ########.fr       */
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
	pipe->before = NULL;
	return(pipe);
}

void	ft_pipeadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*last_lst;

	if (!*lst)
	{
		*lst = new;
		new->before = NULL;
	}
	else
	{
		last_lst = ft_pipelast(*lst);
		last_lst->next = new;
		new->before = last_lst;
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
	t_pipe	*next;

	if (lst)
	{
		begin = *lst;
		while (begin)
		{
			next = begin->next;
			ft_pipedelone(begin);
			begin = next;
			if(begin)
				begin->before = NULL;
		}
		*lst = NULL;
	}
}
