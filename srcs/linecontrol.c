/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:38 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/09 21:33:16 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_control(char *readl, int *s_f, int *d_f, int i)
{
	if(readl[i] == '"' && (*d_f == 0 && *s_f == 0))
		*d_f = 1;		
	else if(readl[i] == '\'' && (*d_f == 0 && *s_f == 0))
		*s_f = 1;
	else if(readl[i] == '"' && *d_f == 1)
		*d_f = 0;
	else if(readl[i] == '\'' && *s_f == 1)
		*s_f = 0;
	else if (readl[i] == '\\' && (readl[i + 1] == '"' || \
		readl[i + 1] == '\'' || readl[i + 1] == '\\'))
		i++;
}

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
		ft_control(readl, &double_flag, &simple_flag, i);
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
	int simple_flag;
	int double_flag;
	char **split_dolar;
	int	d_quotes;
	int	s_quotes;
	int dolar_cont;
	
	simple_flag = 0;
	double_flag = 0;
	d_quotes = 0;
	s_quotes = 0;
	dolar_cont = 0;
	i = -1;
	while (dolar[++i])
	{
		j = -1;
		while (dolar[i][++j])
		{
			if (dolar[i][j]	== 36)
				dolar_cont++;
		}
		if(dolar_cont > 0)
		{
			if(ft_strchr(dolar[i], 39))
				s_quotes = 1;
			if(ft_strchr(dolar[i], 34))
				d_quotes = 1;
			if (s_quotes == 0 && d_quotes == 0) //No hay comillas
			{
				if (dolar_cont == 1)
				{
					ft_one_dolar(&dolar[i], envp);
					dolar_cont = 0;
				}
				else
				{
					split_dolar = ft_split(dolar[i], '$');
					ft_multi_dolar(&dolar[i], envp, split_dolar, dolar_cont);
					dolar_cont = 0;
				}
			}
			else if (s_quotes == 1 && d_quotes == 0) //solo hay comillas simples
			{
				if (is_inside_quotes('\'', dolar[i]) == 0)
				{
					if (dolar_cont == 1)
					{
						ft_one_dolar(&dolar[i], envp);
						dolar_cont = 0;
					}
					else
					{
						split_dolar = ft_split(dolar[i], '$');
						ft_multi_dolar(&dolar[i], envp, split_dolar, dolar_cont);
						dolar_cont = 0;
					}
				}
			}
		}
		printf("%s\n", dolar[i]);
			
	/* 		cont = 0;
				
			while(dolar[i][cont] != '$')
				cont++;
			aux_join = ft_substr(dolar[i], 0, cont);
			dolar[i] = ft_substr(dolar[i], cont + 1, ft_strlen(dolar[i]) - cont);
		}
		j = -1;
		while (dolar[i][++j])
		{
			if(dolar[i][j] == '\'')
				simple_flag = 1;
			if(dolar[i][j] == '"') 
				double_flag = 1;

			if(dolar[i][j] == '$')
			{
				if(dolar[i][j + 1] && simple_flag == 0 && double_flag == 0)
					dolar[i] = ft_substr(dolar[i], 1, ft_strlen(dolar[i]) - 1);
				printf("---->%s\n", dolar[i]);
				if(dolar[i][ft_strlen(dolar[i]) - 1] == '"' && double_flag == 1)
				{
					dolar[i] = ft_substr(dolar[i], 2, ft_strlen(dolar[i]) - 3);
				}
				aux = ft_lstfind_env_val(envp, dolar[i]);
				if (!aux)
				{
					if (simple_flag == 1 && dolar[i][j - 1] == '\'' && dolar[i][ft_strlen(dolar[i]) - 1] == '\'')
						dolar[i] = ft_substr(dolar[i], 1, ft_strlen(dolar[i]) - 2);
					printf("$----->%s\n", dolar[i]);
					continue;
					//dolar[i] = "";
				}
				else
				{
					free(dolar[i]);
					dolar[i] = ft_strdup(aux);
					printf("------>%s\n", dolar[i]);
					break ;
				}
			} 
		}*/
	}
	return (0);
}