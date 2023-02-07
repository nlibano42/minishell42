/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:35:42 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/07 21:34:34 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
	printf("lsdtfind--entra\n");
	name = "PATH";

	while (lst)
	{
		printf("name: %s\n", lst->name);
		printf("val: %s\n", lst->val);
		
		if (lst->name == name)
			return (lst->val);
		lst = lst->next;
	}
	return (NULL);
}