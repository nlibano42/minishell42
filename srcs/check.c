/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:18 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/18 17:09:08 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
		write(2,"Minishell: Error. Unclosed quotes\n", 34);
		free (s);
		return (g_shell.quit_status = 1);
	}
	return (0);
}
