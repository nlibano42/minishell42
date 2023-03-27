/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:00:11 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/27 21:47:46 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static size_t	get_split_size(char const *s, char c)
{
	size_t		count;
	t_quotes	quotes;

	init_quotes_flags(&quotes);
	count = 0;
	while (*s)
	{
		while ((*s != c || (*s == c && (quotes.flag_d == 1 || \
			quotes.flag_s == 1))) && *s)
		{
			check_quotes_flags(&quotes, *s);
			s++;
		}
		count++;
		while ((*s == c && quotes.flag_d == 0 && quotes.flag_s == 0) && *s)
		{
			check_quotes_flags(&quotes, *s);
			s++;
		}
	}
	return (count);
}

static char	**split_add(const char *s, char **dst, size_t i, size_t len)
{
	dst[i] = (char *)malloc(sizeof(char) * len + 1);
	if (!dst[i])
	{
		while (i)
			free (dst[--i]);
		free(dst);
		return (NULL);
	}
	ft_strlcpy(dst[i], s - len, len + 1);
	return (dst);
}

static void	split_while(const char *s, char c, size_t *i, char **dst)
{
	t_quotes	quotes;
	size_t		len;

	init_quotes_flags(&quotes);
	while (*s)
	{
		len = 0;
		while ((*s != c || (*s == c && (quotes.flag_d == 1 || \
			quotes.flag_s == 1))) && *s)
		{
			check_quotes_flags(&quotes, *s);
			len++;
			s++;
		}
		if (len > 0)
		{
			dst = split_add(s, dst, *i, len);
			*i += 1;
		}
		while ((*s == c && (quotes.flag_d == 0 && quotes.flag_s == 0)) && *s)
		{
			check_quotes_flags(&quotes, *s);
			s++;
		}
	}
}

char	**split(char const *s, char c)
{
	char		**dst;
	size_t		i;

	if (!s)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (get_split_size(s, c) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	split_while(s, c, &i, dst);
	dst[i] = NULL;
	return (dst);
}

char	**subsplit(char **sp, int start, int len)
{
	char	**s;
	int		i;
	char	*cmd;
	char	*str;

	s = (char **)malloc(sizeof(char *) * (len + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (--len >= 0)
	{
		cmd = ft_deletequotes(sp[0]);
		str = ft_strtrim(sp[start], " ");
		if (!is_builtin(cmd))
			s[i] = ft_deletequotes(str);
		else
			s[i] = ft_strdup(str);
		free(str);
		i++;
		start++;
		free(cmd);
	}
	s[i] = NULL;
	return (s);
}
