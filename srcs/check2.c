/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:54:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/25 20:06:33 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_spaces(char *readl)
{
	int	i;

	i = -1;
	while (readl[++i])
	{
		if (readl[i] != ' ')
			return (0);
	}
	return (1);
}

int	export_check_null(char *val, char *str, char *cmd)
{
	if (!val)
	{
		free(val);
		return (error_export(str, cmd));
	}
	return (0);
}

int	export_check(char *val, char *str, char *cmd)
{
	int		i;

	if (export_check_null(val, str, cmd) != 0)
		return (1);
	i = -1;
	while (val[++i])
	{
		if (val[i] != '_')
		{
			if (isalnum(val[i]) == 0)
			{
				free(val);
				return (error_export(str, cmd));
			}
		}
	}
	if (ft_isdigit(val[0]))
	{
		free(val);
		return (error_export(str, cmd));
	}
	free(val);
	free(str);
	return (0);
}

void	ft_control(char *readl, t_quotes *quotes, int i)
{
	check_quotes_flags(quotes, readl[i]);
	if (readl[i] == '\\' && (readl[i + 1] == '"' || \
		readl[i + 1] == '\'' || readl[i + 1] == '\\'))
		i++;
}

int	is_digit(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit((int)s[i]))
			return (1);
	}
	return (0);
}
