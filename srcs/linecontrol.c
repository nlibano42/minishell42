/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:33:38 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/11 16:10:00 by nlibano-         ###   ########.fr       */
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
	t_quotes	quotes;

	init_quotes_flags(&quotes);
	quotes.join_str = expand_dolar(s, env, &quotes);
	quotes.join_str = expand_virgulilla(s, env, &quotes);
	if (quotes.join_str != NULL)
	{
		free (*s);
		*s = ft_strdup(quotes.join_str);
		free(quotes.join_str);
	}
}

char	*expand_dolar(char **str, t_env *env, t_quotes *quotes)
{
	int		i;
	char	*s;

	s = *str;
	i = -1;
	while (s[++i])
	{
		check_quotes_flags(quotes, s[i]);
		dollar_exchange(s, &i, quotes, env);
	}
	return (quotes->join_str);
}

void	dollar_exchange(char *s, int *i, t_quotes *quotes, t_env *env)
{
	if (s[*i] =='$' && find_str(s[*i + 1], "\"\'") == 1\
		&& quotes->flag_s == 0 && quotes->flag_d == 0)
	{
		quotes->join_str = ft_strdup("");
		quotes->join_str = change_env_val(s, env, i, quotes->join_str);
	}
	else if (s[*i] == '$' && quotes->flag_s == 0 &&\
		find_str(s[*i + 1], "|\"\'$>< ") == 0) 
	{
		if (s[*i + 1] == '?')
		{	
			quotes->join_str = ft_strdup("");
			quotes->join_str = change_quitvalue(s, i, quotes->join_str);
		}
		else if (s[*i + 1] != ' ' && s[*i + 1])
		{
			quotes->join_str = ft_strdup("");
			quotes->join_str = change_env_val(s, env, i, quotes->join_str);
		}
	}
}
