/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:38 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/06 20:03:38 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_controlcomillas(char *readl)
{
	int i;
	int simple_flag;
	int double_flag;

	simple_flag = 0;
	double_flag = 0;
	i = -1;
	while(readl[++i])
	{
		if(readl[i] == ' ' && (double_flag == 0 && simple_flag == 0))
			readl[i] = ',';
		if(readl[i] == '"' && (double_flag == 0 && simple_flag == 0))
			double_flag = 1;		
		else if(readl[i] == '\'' && (double_flag == 0 && simple_flag == 0))
			simple_flag = 1;
		else if(readl[i] == '"' && double_flag == 1)
			double_flag = 0;
		else if(readl[i] == '\'' && simple_flag == 1)
			simple_flag = 0;
		else if (readl[i] == '\\' && (readl[i + 1] == '"' || readl[i + 1] == '\'' || readl[i +1] == '\\'))
			i++;
		 //mirar lo que es el NULL del final
	}
	return(readl);
}

int linecontrol(char *readl)
{
	char	*aux;
	char	*aux_cmd;
	char	**split_cmd;
	
	aux = readl;
	aux_cmd = ft_controlcomillas(aux);
	expand(ft_split(aux_cmd, ","));
	return (1);
} 

int	expand(char **readl)
{
	int	i;
	int	j;

	i = -1;
	while (readl[++i])
	{
		
	}
	return (0);
}