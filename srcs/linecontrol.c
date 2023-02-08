/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:38 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/07 21:29:01 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


char	*ft_controlcomillas(char *readl)
{
	int i;
	int simple_flag;
	int double_flag;
	char *output;

	simple_flag = 0;
	double_flag = 0;
	output = malloc(sizeof(char) * ft_strlen(readl) + 5);
	if(!output)
		return(NULL);
	i = -1;
	while(readl[++i])
	{
		if(readl[i] == ' ' && (double_flag == 0 && simple_flag == 0))
		{
			output[i] = ',';
			continue ;
		}
		if(readl[i] == '"' && (double_flag == 0 && simple_flag == 0))
			double_flag = 1;		
		else if(readl[i] == '\'' && (double_flag == 0 && simple_flag == 0))
			simple_flag = 1;
		else if(readl[i] == '"' && double_flag == 1)
			double_flag = 0;
		else if(readl[i] == '\'' && simple_flag == 1)
			simple_flag = 0;
		else if (readl[i] == '\\' && (readl[i + 1] == '"' || readl[i + 1] == '\'' || readl[i + 1] == '\\'))
			i++;
		output[i] = readl[i];
	}
	output[i] = ',';
	output[i + 1] = '\0';
	return(output);
}

int	linecontrol(char *readl, t_env *envp)
{
	char	*aux;
	char	*aux_cmd;
	
	aux = readl;
	aux_cmd = ft_controlcomillas(aux);
	free(aux);
	expand(ft_split(aux_cmd, ','), envp);
	return (1);
} 

int	expand(char **dolar, t_env *envp)
{
	int	i;
	int	j;
	char *aux;
	
	i = -1;
	while (dolar[++i])
	{
		j = -1;
		while (dolar[i][++j])
		{
			if(dolar[i][j] == '$')
			{
				if(dolar[i][j + 1])
				{
					printf("---->entra\n");
					dolar[i] = ft_substr(dolar[i], 1, ft_strlen(dolar[i] - 1));
				}
				printf("---->%s\n", dolar[i]);
				aux = ft_lstfind_env_val(envp, dolar[i]);
				if (!aux)
					dolar[i] = "";
				else
				{
					free(dolar[i]);
					dolar[i] = ft_strdup(aux);
				printf("------>%s\n", dolar[i]);
					break ;
				}
			} 
		}
	}
	return (0);
}