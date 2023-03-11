/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:18 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/07 22:00:57 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_init_params(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		printf("Error. Incorrect parameters\n");
		return (1);
	}
	return (0);
}

void	check_quotes_flags(t_quotes *quotes, char c)
{
	if (c == '\'' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_s = 1;
	else if (c == '"' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_d = 1;
	else if (c == '"' && quotes->flag_d == 1 && quotes->flag_s == 0)
		quotes->flag_d = 0;
	else if (c == '\'' && quotes->flag_d == 0 && quotes->flag_s == 1)
		quotes->flag_s = 0;
}

int	is_quotes_opened(char *s)
{
	t_quotes	quotes;
	int			i;

	init_quotes_flags(&quotes);
	i = -1;
	while (s[++i])
		check_quotes_flags(&quotes, s[i]);
	if (quotes.flag_d == 1 || quotes.flag_s == 1)
	{
		ft_putstr_fd("Minishell: Error. Unclosed quotes\n", 2);
		free (s);
		return (g_shell.quit_status = 1);
	}
	return (0);
}

int	is_two_pipes(char *s)
{
	t_quotes	quotes;
	int			i;
	char		**sp;

	init_quotes_flags(&quotes);
	sp = ft_split(s, '\n');
	i = -1;
	while (sp[++i])
	{
		check_quotes_flags(&quotes, s[i]);
		if (sp[i][0] == '|' && sp[i + 1][0] == '|'\
			&& quotes.flag_d == 0 && quotes.flag_s == 0)
		{
			ft_putstr_fd("Minishell: Error. not allowed two pipes\n", 2);
			free (s);
			return (g_shell.quit_status = 1);
		}
	}
	return (0);
}

int	is_open_pipe(char *s)
{
	t_quotes	quotes;
	int			i;

	init_quotes_flags(&quotes);
	s = ft_strtrim(s, " ");
	i = -1;
	while (s[++i])
	{
		check_quotes_flags(&quotes, s[i]);
		if ((s[i] == '|' && !(s[i + 1]) \
			&& quotes.flag_d == 0 && quotes.flag_s == 0) || s[0] == '|')
		{
			ft_putstr_fd("Minishell: Error pipe\n", 2);
			free (s);
			return (g_shell.quit_status = 1);
		}
	}
	return (0);
}
