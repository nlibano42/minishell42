/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:35:42 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/22 00:05:34 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init_env(t_env **envi, char **env)
{
	t_env	*new;
	char	**values;
	int		i;

	i = -1;
	while (env[++i])
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
		if (ft_strlen(lst->name) == ft_strlen(name) && \
				ft_strcmp(lst->name, name) == 0)
			return (lst->val);
		lst = lst->next;
	}
	return (NULL);
}

char	**tab_env(t_env *env)
{
	char	**tab;
	int		i;
	char	*s;
	t_env	*envi;

	envi = env;
	i = 1;
	while (envi)
	{
		i++;
		envi = envi->next;
	}
	tab = (char **)malloc((sizeof(char *) * i + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (env)
	{
		s = ft_strjoin(ft_deletequotes(env->name), ft_strdup("="));
		s = ft_strjoin(s, ft_deletequotes(env->val));
		tab[++i] = s;
		env = env->next;
	}
	tab[i + 1] = NULL;
	return (tab);
}

void	env(t_cmd *cmd)
{
	t_env	*env;

	env = cmd->env;
	while (env)
	{
		if (ft_strcmp(env->val, ""))
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->val, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
}
