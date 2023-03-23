/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:54:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/23 21:50:55 by jdasilva         ###   ########.fr       */
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

int	export_check(char *val)
{
	int		i;

	if (!ft_strcmp(val, "="))
		return (error_export(val));
	i = -1;
	while (val[++i])
	{
		if (val[i] != '_')
		{
			if (isalnum(val[i]) == 0)
				return (error_export(val));
		}
	}
	free(val);
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

void	ft_status(int status)
{	
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_shell.quit_status = 130;
		else if ((WTERMSIG(status) == 3))
			g_shell.quit_status = 131;
	}
	
	if (WIFEXITED(status))
	{	
		
		if(g_shell.quit_status == 256)
			g_shell.quit_status = 1;
		else if (status == 256)
			g_shell.quit_status = WEXITSTATUS(status) + 126;
		else
			g_shell.quit_status = WEXITSTATUS(status);
	}
}

void	ft_status_heredoc(int status)
{
	if (WIFEXITED(status))
	{
		if (status == 256)
			g_shell.quit_status = 256;
		else
			g_shell.quit_status = WEXITSTATUS(status);
	}
}