/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:13:35 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/20 11:30:25 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_deletequotes(char *s)
{
	t_quotes	quotes;
	int			start;
	int			i;
	char		*res;

	init_quotes_flags(&quotes);
	quotes.join_str = ft_strdup("");
	start = 0;
	i = -1;
	if (!s)
	{
		free(quotes.join_str);
		return (s);
	}
	while (s[++i])
	{
		check_quotes_flags(&quotes, s[i]);
		if ((s[i] == '"' && quotes.flag_s == 0) || \
			(s[i] == '\'' && quotes.flag_d == 0))
		{
			quotes.join_str = ft_strjoin(quotes.join_str, \
				ft_substr(s, start, i - start));
			start = i + 1;
		}
	}
	if (start < i)
		quotes.join_str = ft_strjoin(quotes.join_str, \
			ft_substr(s, start, i - start));
	//free(s); TODO:liberar lugar correspondiente.
	res = ft_strdup(quotes.join_str);
	free(quotes.join_str);
	return (res);
}
