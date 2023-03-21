/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:54:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/21 19:39:36 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_spaces(char *readl)
{
	int	i;

	i = -1;
	while (readl[++i])
	{
		if (readl[i] != ' ')
			return (0);
	}
	return (1);
}

int	is_fin_redirection(char *str)
{
	t_quotes	quotes;
	int			i;
	int			j;
	char		*s;

	init_quotes_flags(&quotes);
	s = ft_strtrim(str, " ");
	i = -1;
	while (s[++i])
	{
		check_quotes_flags(&quotes, s[i]);
//		if (s[i] == '<' && s[i + 1] == '\0' && quotes.flag_d == 0 && quotes.flag_s == 0)
//			return (redirections_error(s, 258));
//		if (s[i] == '>' && s[i + 1] == '\0' && quotes.flag_d == 0 && quotes.flag_s == 0)
//			return (redirections_error(s, 258));
//		if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '\0' && quotes.flag_d == 0 && quotes.flag_s == 0)
//			return (redirections_error(s, 258));
//		if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '\0' && quotes.flag_d == 0 && quotes.flag_s == 0)
//			return (redirections_error(s, 258));
//		if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>' && quotes.flag_d == 0 && quotes.flag_s == 0)
//			return (redirections_error(s, 258));
//		if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<' && quotes.flag_d == 0 && quotes.flag_s == 0)
//			return (redirections_error(s, 258));
		//------------------------------------//
		if (s[i] == '>' && s[i + 1] == '<' && quotes.flag_d == 0 && quotes.flag_s == 0)
			return (redirections_error(s, 258));
		if ((s[i] == '<' || s[i] == '>') && quotes.flag_d == 0 && quotes.flag_s == 0)
		{
			if (s[i + 1] == '<' || s[i + 1] == '>')
				j = i + 2;
			else
				j = i + 1;
			while (s[j] == ' ')
				j++;
			if (!s[j] || s[j] == '|' || s[j] == '<' || s[j] == '>')
				return (redirections_error(s, 258));
		}
	}
	free(s);
	return (0);
}

int	export_check(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] == '=')
		{
			ft_putstr_fd("minishel: export: ", 2);
			ft_putstr_fd("\'", 2);
			ft_putstr_fd(ft_deletequotes(cmd[i]), 2);
			ft_putstr_fd("\'", 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (g_shell.quit_status = 1, 1);
		}		
	}
	return (0);
}

void	ft_control(char *readl, t_quotes *quotes, int i)
{
	check_quotes_flags(quotes, readl[i]);
	if (readl[i] == '\\' && (readl[i + 1] == '"' || \
		readl[i + 1] == '\'' || readl[i + 1] == '\\'))
		i++;
}

int	is_digit(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit((int)s[i]))
			return (1);
	}
	return (0);
}
