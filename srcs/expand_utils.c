/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:07:35 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/17 00:15:52 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*change_env_virgu(char *s, t_env *env, int *i, char *join_str)
{
	char	*virgu;

	if (!ft_strcmp(s, "~") || !ft_strncmp(s, "~/", 2))
	{
		virgu = ft_strdup(ft_lstfind_env_val(env, "HOME"));
		if (s[*i + 1] == '/')
		{
			join_str = ft_strjoin(virgu, ft_substr(s, *i + 1, \
				ft_strlen(s) - 1));
			return (join_str);
		}
		else
			return (virgu);
	}
	return (join_str = ft_strdup(s));
}

char	*change_quitvalue(char *s, int *i, char *join_str)
{
	char	*val;

	if (*i != 0)
		join_str = ft_strjoin(join_str, ft_substr(s, 0, *i));
	val = ft_itoa(g_shell.quit_status);
	join_str = ft_strjoin(join_str, val);
	*i = ft_strlen(join_str);
	if (s[*i + 1])
		join_str = ft_strjoin(join_str, \
			ft_substr(s, *i + 1, ft_strlen(s) - 1));
	return (join_str);
}

char	*expand_virgulilla(char **str, t_env *env, t_quotes *quotes)
{
	char	*s;
	int		i;

	s = *str;
	i = -1;
	while (s[++i])
	{
		check_quotes_flags(quotes, s[i]);
		if (s[i] == '~' && (quotes->flag_s == 0 || quotes->flag_d == 0) \
			&& i == 0)
		{
			quotes->join_str = ft_strdup("");
			quotes->join_str = change_env_virgu(s, env, &i, quotes->join_str);
		}
	}
	return (quotes->join_str);
}

char	*change_env_val(char *s, t_env *env, int *i, char *join_str)
{
	char	*str;
	int		fin;
	char	*val;

	str = NULL;
	if (*i != 0)
		join_str = ft_strjoin(join_str, ft_substr(s, 0, *i));
	fin = find_fin_str(s, *i);
	str = ft_substr(s, *i + 1, fin - (*i + 1));
	*i += ft_strlen(str);
	val = ft_strdup(ft_lstfind_env_val(env, str));
	join_str = ft_strjoin(join_str, val);
	free (str);
	if (s[*i + 1])
		join_str = ft_strjoin(join_str, \
		ft_substr(s, *i + 1, ft_strlen(s) - 1));
	return (join_str);
}
