/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:41:00 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/22 17:47:11 by nlibano-         ###   ########.fr       */
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
	pipe->wait = 0;
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
	int	i;

	if (pipe)
	{
		if (pipe->full_cmd)
			free_split(pipe->full_cmd);
		if (pipe->redir)
		{
			i = -1;
			while (++i < pipe->num_redi)
			{
				if (pipe->redir[i].file)
					free(pipe->redir[i].file);
				if (pipe->redir[i].key)
					free(pipe->redir[i].key);
			}
			free(pipe->redir);
		}
		if (pipe->path)
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
