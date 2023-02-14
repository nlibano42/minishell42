/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:13:35 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/14 19:10:26 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_deletequotes(char *s)
{
	t_quotes	quotes;
	int			start;
	int			i;

	quotes.join_str = ft_strdup("");
	quotes.flag_d = 0;
	quotes.flag_s = 0;
	start = 0;
	i = -1;
	while(s[++i])
	{
		ft_quotes_crontol(s, &quotes, &i);
		if ((s[i] == '"' && quotes.flag_s == 0) || (s[i] == '\'' && quotes.flag_d == 0))
		{
			quotes.join_str = ft_join_str(quotes.join_str, ft_substr(s, start, i - start));
			start = i + 1;
		}
	}
	if (start < i)
		quotes.join_str = ft_join_str(quotes.join_str, ft_substr(s, start, i - start));
	free(s);
	s = ft_strdup(quotes.join_str);
	free(quotes.join_str);
	return(s);
}