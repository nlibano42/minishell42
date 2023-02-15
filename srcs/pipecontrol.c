/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:14:45 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/16 00:48:44 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_pipecontrol(char *s)
{
	t_quotes	quotes;
	int			start;
	int			i;
	char		*s1;

	init_quotes_flags(&quotes);
	quotes.join_str = ft_strdup("");
	start = 0;
	i = -1;
	while(s[++i])
	{
		check_quotes_flags(&quotes, s[i]);
		if((s[i] == '|' || s[i] == '<'  || s[i] == '>') && quotes.flag_d == 0  && quotes.flag_s == 0)
		{
			s1 = ft_substr(s, start, i - start);
			if (s[i - 1] != ',')
				s1 = ft_join_str(s1, ft_strdup(","));
			quotes.join_str = ft_join_str(quotes.join_str, s1);
			if((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<'))
				s1 = ft_substr(s, i, 2);
			else
				s1 = ft_substr(s, i, 1);
			quotes.join_str = ft_join_str(quotes.join_str, s1);
			if (s[i + 1] != ',')
				quotes.join_str = ft_join_str(quotes.join_str, ft_strdup(","));
			if((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<'))
			{
				start = i + 2;
				i++;
			}
			else
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