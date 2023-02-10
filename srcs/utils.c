/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:46:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/09 20:47:53 by jdasilva         ###   ########.fr       */
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

int	is_inside_quotes(char quotes, char *s)
{
	int	i;
	int	flag;
	
	i = -1;
	flag = 0;
	while (s[++i])
	{
		if (s[i] == quotes && flag == 0)
			flag = 1;
		else if (s[i] == quotes && flag == 1)
			flag = 0;
		if (s[i] == '$' && flag == 1)
			return (1) ;
	}
	return (0);
	
}