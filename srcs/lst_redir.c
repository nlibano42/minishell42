/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:25:23 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/12 15:16:19 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*t_redir	*ft_lstnew_redir(void)
{
	t_redir	*list;

	list = malloc(sizeof(t_redir));
	if (!list)
		return (NULL);
	list->key = NULL;
	list->file = NULL;
	list->type = NULL;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last_lst;

	if (!*lst)
		*lst = new;
	else
	{
		last_lst = ft_lstlast_redir(*lst);
		last_lst->next = new;
	}
}

void	ft_lstclear_redir(t_redir **lst)
{
	t_redir	*begin;

	if (lst)
	{
		while (*lst)
		{
			begin = (*lst)->next;
			ft_lstdelone_redir(*lst);
			*lst = begin;
		}
	}
}

void	ft_lstdelone_redir(t_redir *lst)
{
	if (lst)
	{
	//	free(lst->name);
	//	free(lst->val);
		free(lst);
	}
}

t_redir	*ft_lstlast_redir(t_redir *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
*/