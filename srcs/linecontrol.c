/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:38 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/13 17:20:04 by jdasilva         ###   ########.fr       */
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
			output[i] = '\n';
			continue ;
		}
		ft_control(readl, &double_flag, &simple_flag, i);
		output[i] = readl[i];
	}
	output[i] = '\n';
	output[i + 1] = '\0';
	return (output);
}

int	linecontrol(t_cmd *cmd, t_env *envp)
{
	char	*aux;
	int		i;

	aux = cmd->readl;
	cmd->cmd_line = ft_controlcomillas(aux);
	free(aux); //liberar readl? necesitaremos mas adelante este valor?
	cmd->cmd = ft_split(cmd->cmd_line, '\n');
	i = -1;
	while (cmd->cmd[++i])
	{
		expand(&(cmd->cmd[i]), envp);
printf("%s\n", cmd->cmd[i]);
	}
	join_split(cmd);
printf("%s\n", cmd->cmd_line);
	return (1);
}

int	join_split(t_cmd *cmd)
{
	int		i;

	free(cmd->cmd_line);
	cmd->cmd_line = ft_strdup("");
	i = -1;
	while (cmd->cmd[++i])
	{
		cmd->cmd_line = ft_join_str(cmd->cmd_line, ft_strdup(cmd->cmd[i]));
		cmd->cmd_line = ft_join_str(cmd->cmd_line, ft_strdup(","));
	}	
	cmd->cmd_line = ft_join_str(cmd->cmd_line, ft_strdup("NULL"));
	return (0);
}

void	expand(char **s, t_env *env)
{
// OJO!!! $USER! -> nlibano!
	int			i;
	t_quotes	quotes;

	quotes.join_str = NULL;
	quotes.flag_d = 0;
	quotes.flag_s = 0;
	i = -1;
	while ((*s)[++i] != '\0')
		quotes.join_str = ft_control_expand(*s, env, &quotes, &i);
	if (quotes.join_str != NULL)
	{
		free (*s);
		*s = ft_strdup(quotes.join_str);
		free(quotes.join_str);
	}
}

char	*ft_control_expand(char *s, t_env *env, t_quotes *quotes, int *i)
{
	if (s[*i] == '\'' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_s = 1;
	else if (s[*i] == '"' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_d = 1;
	else if (s[*i] == '\'' && quotes->flag_d == 1 && quotes->flag_s == 0)
		quotes->flag_d = 0;
	else if (s[*i] == '\'' && quotes->flag_d == 0 && quotes->flag_s == 1)
		quotes->flag_s = 0;
	else if (s[*i] == '$' && quotes->flag_s == 0 && \
			find_str(s[*i + 1], "|\"\'$?>< ") == 0) 
	{
		quotes->join_str = ft_strdup("");
		quotes->join_str = ft_parching_dolar(s, env, *i, quotes->join_str);
	}
	return (quotes->join_str);
}

char	*ft_parching_dolar(char *s, t_env *env, int i, char *join_str)
{
	char	*str;
	int		fin;
	char	*val;

	// cogemos la primera parte del string si i != 0
	if (i != 0)
		join_str = ft_join_str(join_str, ft_substr(s, 0, i));
	// cogemos la parte a sustituir ej: $USER
	fin = find_fin_str(s, i);
	str = ft_substr(s, i + 1, fin - (i + 1));
	i += ft_strlen(str);
	val = ft_strdup(ft_lstfind_env_val(env, str));
	join_str = ft_join_str(join_str, val);
	free (str);
	// cogemos la parte final del string si i != '\0'
	if (s[i + 1])
		join_str = ft_join_str(join_str,
				ft_substr(s, i + 1, ft_strlen(s) - 1));
	return (join_str);
}