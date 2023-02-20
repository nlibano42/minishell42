/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipecontrol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:14:45 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/20 18:50:28 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	join_with_space(char *s, int *i, t_quotes *quotes, int *start)
{
	char	*s1;

	s1 = ft_substr(s, *start, *i - *start);
	if (*i != 0 && s[*i - 1] != ' ')
		s1 = ft_strjoin(s1, ft_strdup(" "));
	quotes->join_str = ft_strjoin(quotes->join_str, s1);
	if ((s[*i] == '>' && s[*i + 1] == '>') || (s[*i] == '<' && s[*i + 1] == '<'))
		s1 = ft_substr(s, *i, 2);
	else
		s1 = ft_substr(s, *i, 1);
	quotes->join_str = ft_strjoin(quotes->join_str, s1);
	if (*i < 0 && s[*i + 1] != ' ')
		quotes->join_str = ft_strjoin(quotes->join_str, ft_strdup(" "));
	if ((s[*i] == '>' && s[*i + 1] == '>') || (s[*i] == '<' && s[*i + 1] == '<'))
	{
		*start = *i + 2;
		*i += 1;
	}
	else
		*start = *i + 1;
}

char	*expand_pipe_redir(char *s)
{
	t_quotes	quotes;
	int			start;
	int			i;

	init_quotes_flags(&quotes);
	quotes.join_str = ft_strdup("");
	start = 0;
	i = -1;
	while (s[++i])
	{
		check_quotes_flags(&quotes, s[i]);
		if ((s[i] == '|' || s[i] == '<' || s[i] == '>') && quotes.flag_d == 0 && quotes.flag_s == 0)
			join_with_space(s, &i, &quotes, &start);
	}
	if (start < i)
		quotes.join_str = ft_strjoin(quotes.join_str, ft_substr(s, start, i - start));
	free(s);
	s = ft_strdup(quotes.join_str);
	free(quotes.join_str);
	return (s);
}

void	count_pipe(t_cmd *cmd, char *s)
{
	t_quotes	quotes;
	int			i;
	
	cmd->num_pipes = 0;
	init_quotes_flags(&quotes);
	i = -1;
	while(s[++i])
	{
		check_quotes_flags(&quotes, s[i]);
		if(s[i] == '|' && quotes.flag_d == 0 && quotes.flag_s == 0)
			cmd->num_pipes ++;
	}
}