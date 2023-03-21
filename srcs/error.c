/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:49:57 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/21 09:52:17 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	access_error(char *input)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	g_shell.quit_status = 1;
}

void	pipe_error(char *error, int num)
{
	perror(error);
	exit(num);
}

void	execve_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	redirections_error(char *s, int num)
{
	ft_putstr_fd("Minishell: syntax error\n", 2);
	free(s);
	return (g_shell.quit_status = num);
}

int	print_error(char *s, int *i)
{
	if (s[*i] == '\0')
	{
printf("---->2\n");
		ft_putstr_fd("Minishell: syntax error\n", 2);
		free(s);
		return (1);
	}
	return (0);
}
