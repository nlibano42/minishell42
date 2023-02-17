/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:28:18 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/16 00:38:44 by nlibano-         ###   ########.fr       */
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

int is_quotes_opened(char *s)
{
	t_quotes quotes;
	int i;

	i = -1;
	while (s[++i])
		check_quotes_flags(&quotes, s[i]);
	if (quotes.flag_s == 1 || quotes.flag_s == 1)
		return (1);
	return (0);
}