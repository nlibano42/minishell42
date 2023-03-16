/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:41:00 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/17 00:25:19 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_pipe	*ft_newpipe(void)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		return (NULL);
	pipe->full_cmd = NULL;
	pipe->path = NULL;
	pipe->next = NULL;
	pipe->redir = NULL;
	pipe->num_redi = 0;
	pipe->before = NULL;
	return (pipe);
}

void	ft_pipeadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*last_lst;

	if (!*lst)
		*lst = new;
	else
	{
		last_lst = ft_pipelast(*lst);
		new->before = last_lst;
		last_lst->next = new;
	}
}

t_pipe	*ft_pipelast(t_pipe *pipe)
{
	while (pipe)
	{
		if (!(pipe->next))
			return (pipe);
		pipe = pipe->next;
	}
	return (pipe);
}

void	ft_pipedelone(t_pipe *pipe)
{
	if (pipe)
	{
		free_split(pipe->full_cmd);
		pipe->full_cmd = NULL;
		if (pipe->redir)
		{
			free(pipe->redir);
			pipe->redir = NULL;
		}
		free(pipe->path);
		pipe->path = NULL;
		free(pipe);
		pipe = NULL;
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
