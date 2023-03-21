/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:08:56 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/21 20:09:42 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	redirections_find_space(char *s, int i, int *j)
{
	if (s[i + 1] == '<' || s[i + 1] == '>')
		*j = i + 2;
	else
		*j = i + 1;
	while (s[*j] == ' ')
		(*j)++;
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
		if (s[i] == '>' && s[i + 1] == '<' && quotes.flag_d == 0 \
				&& quotes.flag_s == 0)
			return (redirections_error(s, 258));
		if ((s[i] == '<' || s[i] == '>') && quotes.flag_d == 0 && \
				quotes.flag_s == 0)
		{
			redirections_find_space(s, i, &j);
			if (!s[j] || s[j] == '|' || s[j] == '<' || s[j] == '>')
				return (redirections_error(s, 258));
		}
	}
	free(s);
	return (0);
}
