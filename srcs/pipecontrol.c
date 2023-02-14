/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:14:45 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/13 21:01:45 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void ft_quotes_crontol(char *s, t_quotes *quotes, int *i)
{
	if (s[*i] == '\'' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_s = 1;
	else if (s[*i] == '"' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_d = 1;
	else if (s[*i] == '"' && quotes->flag_d == 1 && quotes->flag_s == 0)
		quotes->flag_d = 0;
	else if (s[*i] == '\'' && quotes->flag_d == 0 && quotes->flag_s == 1)
		quotes->flag_s = 0;
}

void ft_pipecontrol(char *s)
{
	t_quotes	quotes;
	int			start;
	int			i;
	char		*s1;

	i = -1;
	quotes.join_str = ft_strdup("");
	quotes.flag_d = 0;
	quotes.flag_s = 0;
	start = 0;
	while(s[++i])
	{
		ft_quotes_crontol(s, &quotes, &i);
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
printf("--->>>> %s\n", quotes.join_str);
}