/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:46:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/08 22:16:04 by jdasilva         ###   ########.fr       */
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
		aux = ft_substr(s, 0, ft_strlen(s) - 1);
	val = ft_strdup(ft_lstfind_env_val(env, aux));
	free(aux);
	return (val);
}