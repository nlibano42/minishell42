/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:38:36 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/22 22:12:02 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_env	*ft_lstnew(char *name, char *val)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	if (!list)
		return (NULL);
	list->name = ft_deletequotes(name);
	if (val)
		list->val = ft_deletequotes(val);
	list->next = NULL;
	return (list);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last_lst;

	if (!*lst)
		*lst = new;
	else
	{
		last_lst = ft_lstlast(*lst);
		last_lst->next = new;
	}
}

void	ft_lstclear(t_env **lst)
{
	t_env	*begin;

	if (lst)
	{
		while (*lst)
		{
			begin = (*lst)->next;
			ft_lstdelone(*lst);
			*lst = begin;
		}
	}
}

void	ft_lstdelone(t_env *lst)
{
	if (lst)
	{
		free(lst->name);
		free(lst->val);
		free(lst);
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
