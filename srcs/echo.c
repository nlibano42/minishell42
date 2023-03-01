/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:04:10 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/01 18:00:29 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	print_echo(char **s, int n)
{
	int		i;
	char	*str;

	i = -1;
	while (s[++i])
	{
		if (i != 0)
			ft_putchar_fd(' ', 1);
		str = ft_deletequotes(s[i]);
		ft_putstr_fd(str, 1);
		free(str);
	}
	if (n == 1)
		ft_putchar_fd('\n', 1);
}

int	echo_find_n_option(char **str, char *s, int i)
{
	int	j;

	j = 0;
	while (s[++j])
	{
		if (s[j] != 'n')
		{
			print_echo(&str[i], i);
			free(s);
			return (1);
		}
	}
	return (0);
}

void	echo(t_cmd *cmd)
{
	char	*s;
	int		i;

	i = 0;
	while (cmd->pipe->full_cmd[++i])
	{
		s = ft_deletequotes(cmd->pipe->full_cmd[i]);
		if (s[0] == '-')
		{
			if (echo_find_n_option(cmd->pipe->full_cmd, s, i))
				return ;
		}
		else
		{
			print_echo(&cmd->pipe->full_cmd[i], i);
			free(s);
			return ;
		}
		free(s);
	}
/* 	if (i == 1)
		ft_putchar_fd('\n', 1); */ //funciona igual sin el.
}
