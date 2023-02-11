/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:38 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/11 20:01:44 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_control(char *readl, int *s_f, int *d_f, int i)
{
	if (readl[i] == '"' && (*d_f == 0 && *s_f == 0))
		*d_f = 1;
	else if (readl[i] == '\'' && (*d_f == 0 && *s_f == 0))
		*s_f = 1;
	else if (readl[i] == '"' && *d_f == 1)
		*d_f = 0;
	else if (readl[i] == '\'' && *s_f == 1)
		*s_f = 0;
	else if (readl[i] == '\\' && (readl[i + 1] == '"' || \
		readl[i + 1] == '\'' || readl[i + 1] == '\\'))
		i++;
}

char	*ft_controlcomillas(char *readl)
{
	int		i;
	int		simple_flag;
	int		double_flag;
	char	*output;

	simple_flag = 0;
	double_flag = 0;
	output = malloc(sizeof(char) * ft_strlen(readl) + 5);
	if (!output)
		return (NULL);
	i = -1;
	while (readl[++i])
	{
		if (readl[i] == ' ' && (double_flag == 0 && simple_flag == 0))
		{
			output[i] = ',';
			continue ;
		}
		ft_control(readl, &double_flag, &simple_flag, i);
		output[i] = readl[i];
	}
	output[i] = ',';
	output[i + 1] = '\0';
	return (output);
}

int	linecontrol(char *readl, t_env *envp)
{
	char	*aux;
	char	*aux_cmd;
	char	**output;
	int		i;

	aux = readl;
	aux_cmd = ft_controlcomillas(aux);
	free(aux);
	output = ft_split(aux_cmd, ',');
	i = -1;
	while (output[++i])
	{
		expand(&(output[i]), envp);
		printf("%s\n", output[i]);
	}
	return (1);
}

void	expand(char **s, t_env *env)
{
	int		i;
	int		flag_d;
	int		flag_s;
	char	*join_str;

	join_str = NULL;
	flag_d = 0;
	flag_s = 0;
	i = -1;
	while ((*s)[++i] != '\0')
	{
		join_str = ft_control_expand(s, env, join_str, &i);
	}
	if (join_str != NULL)
	{
		free (*s);
		*s = ft_strdup(join_str);
		free(join_str);
	}
}

char	*ft_control_expand(char **s, t_env *env, char *join_str, int *i)
{
	int		flag_d;
	int		flag_s;
	int		value;

	flag_d = 0;
	flag_s = 0;
	if ((*s)[*i] == '\'' && flag_d == 0 && flag_s == 0)
		flag_s = 1;
	else if ((*s)[*i] == '"' && flag_d == 0 && flag_s == 0)
		flag_d = 1;
	else if ((*s)[*i] == '\'' && flag_d == 1 && flag_s == 0)
		flag_d = 0;
	else if ((*s)[*i] == '\'' && flag_d == 0 && flag_s == 1)
		flag_s = 0;
	else if ((*s)[*i] == '$' && flag_s == 0 && \
			find_str((*s)[*i + 1], "|\"\'$?>< ") == 0)
	{
		join_str = ft_strdup("");
		value = *i;
		join_str = ft_parching_dolar(s, env, value, join_str);
	}
	return (join_str);
}

char	*ft_parching_dolar(char **s, t_env *env, int i, char *join_str)
{
	char	*str;
	int		fin;
	char	*val;

	// cogemos la primera parte del string si i != 0
	if (i != 0)
		join_str = ft_join_str(join_str, ft_substr(*s, 0, i));
	// cogemos la parte a sustituir ej: $USER
	fin = find_fin_str(*s, i);
	str = ft_substr(*s, i + 1, fin - (i + 1));
	i += ft_strlen(str);
	val = ft_strdup(ft_lstfind_env_val(env, str));
	join_str = ft_join_str(join_str, val);
	free (str);
	// cogemos la parte final del string si i != '\0'
	if ((*s)[i + 1])
		join_str = ft_join_str(join_str,
				ft_substr(*s, i + 1, ft_strlen(*s) - 1));
	return (join_str);
}