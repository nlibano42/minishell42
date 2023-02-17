/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:46:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/15 22:30:25 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*find_change_str(char *s, t_env *env)
{
	char	*aux;
	char	*val;

	if (s[0] == '$')
		aux = ft_substr(s, 1, ft_strlen(s) - 1);
	else
		aux = ft_substr(s, 0, ft_strlen(s));
	val = ft_strdup(ft_lstfind_env_val(env, aux));
	free(aux);
	return (val);
}

int	find_str(char c, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (c == s[i])
			return (1);
	}
	return (0);
}

/*
char	*ft_join_str(char *s1, char *s2)
{
	char	*aux;

	aux = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (aux);
}
*/

int	find_fin_str(char *s, int i)
{
	while (s[++i])
	{
		if (ft_isalnum(s[i]) == 0) 
			return (i);
	}
	return (i);
}
