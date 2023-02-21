/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:41:00 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/21 18:03:00 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_pipe	*ft_newpipe()
{
	t_pipe *pipe;
	
	pipe = malloc(sizeof(t_pipe));
	if(!pipe)
		return (NULL);
	pipe->infile = 0;
	pipe->outfile = 0;
	pipe->next = NULL;
}

void	ft_pipeadd_back(t_pipe **pipe, t_pipe *new)
{
	t_pipe	*last_pipe;

	if(!*pipe)
		*pipe = new;
	else
	{
		last_pipe = ft_pipelast(*pipe);
		last_pipe = new;
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
		free(pipe->full_cmd);
		free(pipe->path);
		free(pipe);
	}
}