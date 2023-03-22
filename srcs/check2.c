/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:54:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/22 22:02:14 by jdasilva         ###   ########.fr       */
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

int	print_error_export(char **cmd, int *i)
{
	ft_putstr_fd("minishel: export: ", 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(ft_deletequotes(cmd[*i]), 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	return(g_shell.quit_status = 1);
}

int	export_check(char **cmd)
{
	int	i;
	int j;

	i = 0;
	while (cmd[++i])
	{
		j = -1;
		while(cmd[i][++j])
		{
			if(ft_isalnum(cmd[i][j]) == 0)
				print_error_export(cmd, &i);
		} 		
		if (cmd[i][0] == '=')
		{
			ft_putstr_fd("minishel: export: ", 2);
			ft_putstr_fd("\'", 2);
			ft_putstr_fd(ft_deletequotes(cmd[i]), 2);
			ft_putstr_fd("\'", 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (g_shell.quit_status = 1, 1);
		}
	}
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
	if (s[0] == '-')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit((int)s[i]))
			return (1);
	}
	return (0);
}
