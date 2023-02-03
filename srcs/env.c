/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:35:42 by nlibano-          #+#    #+#             */
/*   Updated: 2022/12/15 04:35:45 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env **envi, char **env)
{
	t_env	*new;
	char	**values;
    int		i;

	i = -1;
    while(env[++i])
    {
        values = ft_split(env[i], '=');
		new = ft_lstnew(values[0], values[1]);
        ft_lstadd_back(envi, new);
		free_split(values);
    }
}

char	*ft_lstfind_env_val(t_env *lst, char *name)
{

	while (lst)
	{
		if (lst->name == name)
			return (lst->val);
		lst = lst->next;
	}
	return (NULL);
}