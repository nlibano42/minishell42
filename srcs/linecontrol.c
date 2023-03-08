/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:38 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/08 20:27:41 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*prepare_split(char *readl)
{
	t_quotes	quotes;
	int			i;
	char		*output;

	init_quotes_flags(&quotes);
	output = malloc(sizeof(char) * ft_strlen(readl) + 5);
	if (!output)
		return (NULL);
	i = -1;
	while (readl[++i])
	{
		if (readl[i] == ' ' && (quotes.flag_d == 0 && quotes.flag_s == 0))
		{
			output[i] = '\n';
			continue ;
		}
		ft_control(readl, &quotes, i);
		output[i] = readl[i];
	}
	output[i] = '\n';
	output[i + 1] = '\0';
	return (output);
}

int	line_parse(t_cmd *cmd, t_env *envp)
{
	char	*aux;
	int		i;

	aux = cmd->readl;
	cmd->cmd_line = prepare_split(aux);
//	free(aux); //liberar readl? necesitaremos mas adelante este valor?
	cmd->cmd = ft_split(cmd->cmd_line, '\n');
	i = -1;
	while (cmd->cmd[++i])
		expand(&(cmd->cmd[i]), envp);
	join_split(cmd);
	cmd->cmd_line = expand_pipe_redir(cmd);
	if (ft_access(cmd->cmd_line) == -1 || is_two_pipes(cmd->cmd_line) == 1)
		return (g_shell.quit_status = 1); 
		//devolvemos el error con el quit_status, luego podemos hacer
		//segun el error el status un write que diga cual es el error, veremos.
	return (0);
}

void	expand(char **s, t_env *env)
{
	int			i;
	t_quotes	quotes;

	init_quotes_flags(&quotes);
	i = -1;
	while ((*s)[++i] != '\0')
	{
		quotes.join_str = expand_dolar(*s, env, &quotes, &i);
		quotes.join_str = expand_virgulilla(*s, env, &quotes, &i);
	}
	if (quotes.join_str != NULL)
	{
		free (*s);
		*s = ft_strdup(quotes.join_str);
		free(quotes.join_str);
	}
}
char	*expand_virgulilla(char*s, t_env *env, t_quotes *quotes, int *i)
{
	check_quotes_flags(quotes, s[*i]);
	if(s[*i] == '~' && (quotes->flag_s == 0 || quotes->flag_d == 0)\
		&& *i == 0)
	{
		quotes->join_str = ft_strdup("");
		quotes->join_str = change_env_virgu(s, env, i, quotes->join_str);
	}
	return(quotes->join_str);
}
char	*expand_dolar(char *s, t_env *env, t_quotes *quotes, int *i)
{
	check_quotes_flags(quotes, s[*i]);
	if (s[*i] == '$' && quotes->flag_s == 0 && \
		find_str(s[*i + 1], "|\"\'$>< ") == 0) 
	{
		if(s[*i + 1] == '?')
		{	
			quotes->join_str = ft_strdup("");
			quotes->join_str = change_quitvalue(s, i, quotes->join_str);
		}
		else
		{
			quotes->join_str = ft_strdup("");
			quotes->join_str = change_env_val(s, env, i, quotes->join_str);
		}
	}
	return (quotes->join_str);
}

char *change_quitvalue(char *s, int *i, char *join_str)
{
	char *val;

	if(*i != 0)
		join_str = ft_strjoin(join_str, ft_substr(s, 0, *i));
	val = ft_itoa(g_shell.quit_status);
	join_str = ft_strjoin(join_str, val);
	*i = ft_strlen(join_str);
	if(s[*i + 1])
		join_str = ft_strjoin(join_str,\
		ft_substr(s, *i + 1, ft_strlen(s) - 1));
	return(join_str);
}

char	*change_env_val(char *s, t_env *env, int *i, char *join_str)
{
	char	*str;
	int		fin;
	char	*val;

	// cogemos la primera parte del string si i != 0
	if (*i != 0)
		join_str = ft_strjoin(join_str, ft_substr(s, 0, *i));
	// cogemos la parte a sustituir ej: $USER
	fin = find_fin_str(s, *i);
	str = ft_substr(s, *i + 1, fin - (*i + 1));
	*i += ft_strlen(str);
	val = ft_strdup(ft_lstfind_env_val(env, str));
	join_str = ft_strjoin(join_str, val);
	free (str);
	// cogemos la parte final del string si i != '\0'
	if (s[*i + 1])
		join_str = ft_strjoin(join_str, \
		ft_substr(s, *i + 1, ft_strlen(s) - 1));
	return (join_str);
}

char	*change_env_virgu(char *s, t_env *env, int *i, char *join_str)
{
	char *virgu;
	
	if(!ft_strcmp(s, "~") || !ft_strncmp(s ,"~/", 2))
	{
		virgu = ft_strdup(ft_lstfind_env_val(env, "HOME"));
		if(s[*i + 1] == '/')
		{
			join_str = ft_strjoin(virgu, ft_substr(s, *i + 1, ft_strlen(s) - 1));
			return(join_str);
		}
		else 
			return(virgu);
	}
	return(join_str = ft_strdup(s)); //libera ese dup??
}