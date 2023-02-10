/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solodolar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:35:05 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/09 19:48:18 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_one_dolar(char **dolar, t_env *envp)
{
	char *aux;
	char **split_dolar;
	char *aux_join;
	
	if ((*dolar)[0] == '$' && (*dolar)[1] !='\0')
		aux = find_change_str(ft_substr(*dolar, 0,\
			ft_strlen(*dolar)), envp);
	else
	{
		aux = find_change_str(ft_strchr(*dolar, 36), envp);
	}
	if ((*dolar)[0] != '$')
	{
		split_dolar = ft_split(*dolar, '$');
		aux_join = ft_strjoin(split_dolar[0], aux);
		free(aux);
		aux = aux_join;
	}
	free(*dolar);				
	*dolar = ft_strdup(aux);
	free(aux);
}
//s_d = split dolar d_c = dolar_count
void	ft_multi_dolar(char **dolar, t_env *envp, char **s_d, int d_c)
{
	int		j;
	int		cont;
	char	*aux;
	
	j = 0;
	if ((*dolar)[0] != '$')
		d_c++;
	else
		j = -1;
	while(++j < d_c)
	{
		aux = find_change_str(s_d[j], envp);
		free(s_d[j]);
		s_d[j] = ft_strdup(aux);
		free(aux);
	}
	free(*dolar);
	*dolar = ft_strdup("");
	cont = -1;
	while(++cont < j)
		ft_dolar_join(dolar, s_d[cont]);
	free_split(s_d);
}

void ft_dolar_join(char **dolar, char *s_d)
{
	char	*aux;
	
	aux = ft_strjoin(*dolar, s_d);
	free(*dolar);
	*dolar = ft_strdup(aux);
	free(aux);
}