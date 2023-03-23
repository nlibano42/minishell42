/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:03:59 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/23 01:01:22 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_exit(t_cmd *cmd)
{
	int	i;

	if (!cmd->readl)
	{
		ft_putstr_fd("\x1b[1A", 1);
		ft_putstr_fd("\033[15C", 1);
	}
	ft_putstr_fd("\b\bexit\n", 1);
	if (cmd->pipe)
	{	
		i = 0;
		while (cmd->pipe->full_cmd[i])
			i++;
		if (i > 1)
			exit_argument(cmd->pipe->full_cmd, i);
		else
			g_shell.quit_status = 0;
	}
	ft_lstclear(&(cmd->env));
	free_all(cmd);
	close(cmd->save_stdin);
	close(cmd->save_stdout);
	exit(g_shell.quit_status);
}

void	exit_argument(char	**full_cmd, int num)
{
	if (is_digit(full_cmd[1]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_shell.quit_status = 255;
	}
	else if (num > 2)
	{	
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_shell.quit_status = 1;
	}
	else
		g_shell.quit_status = ft_atoi(full_cmd[1]);
}
