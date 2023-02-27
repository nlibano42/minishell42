/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:54:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/27 19:31:42 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int check_spaces(char *readl)
{
	int i;

	i = -1;
	while(readl[++i])
	{
		if(readl[i] != ' ')
			return(0);
	}
	return (1);
}

int	is_fin_redirection(char *s)
{
	t_quotes quotes;
	int i;

	init_quotes_flags(&quotes);
	ft_strtrim(s, " ");
	i = -1;
	while (s[++i])
	{
		check_quotes_flags(&quotes, s[i]);
		if((s[i] == '<' || s[i] == '>') && quotes.flag_d == 0\
			&& quotes.flag_s == 0)
		{
			if(s[i + 1] == '<' || s[i + 1] == '>')
				i++;
			if (s[i + 1] == '\0')
			{
				ft_putstr_fd("Minishell: syntax error\n", 2);
				free(s);
				return(g_shell.pid = 258);
			}
		}
	}
	return (0);
}

int export_check(char **cmd)
{
	int i;

	i = 0;
	while(cmd[++i])
	{
		if(cmd[i][0] == '=')
		{
			ft_putstr_fd("minishel: export: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (g_shell.quit_status = 1, 1);
		}		
	}
	return (0);
}