/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:14:45 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/13 19:16:45 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void ft_quotes_crontol(char *s, t_quotes *quotes, int *i)
{
	if (s[*i] == '\'' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_s = 1;
	else if (s[*i] == '"' && quotes->flag_d == 0 && quotes->flag_s == 0)
		quotes->flag_d = 1;
	else if (s[*i] == '\'' && quotes->flag_d == 1 && quotes->flag_s == 0)
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
	char		*s2;

	i = -1;
	quotes.join_str = NULL;
	quotes.flag_d = 0;
	quotes.flag_s = 0;
	start = 0;
	while(s[++i])
	{
		ft_quotes_crontol(s, &quotes, &i);
		if((s[i] == '|' || s[i] == '<'  || s[i] == '>') && quotes.flag_d == 0  && quotes.flag_s == 0)
		{
			if(ft_isalnum(s[i - 1]) == 1)
				s1 = ft_substr(s, start, i - start);
			else
				s1 = ft_substr(s, start, i - 1 - start);
			s2 = ft_strjoin(s1, ",");
			free(s1);
			s1 = ft_strdup(&s[i]);
			quotes.join_str = ft_join_str(s2, s1);
			printf("join--->%s\n", quotes.join_str);
		}
		
	}
}