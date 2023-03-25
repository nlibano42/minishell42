/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 01:03:59 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/25 18:02:45 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_close_exit(t_cmd *cmd)
{
	free_all(cmd);
	close(cmd->save_stdin);
	close(cmd->save_stdout);
	exit(g_shell.quit_status);
}

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
		{
			if (exit_argument(cmd->pipe->full_cmd, i) == 1)
				return ;
		}
		else
			g_shell.quit_status = 127;
	}
	ft_lstclear(&(cmd->env));
	ft_close_exit(cmd);
}

int	exit_argument(char	**full_cmd, int num)
{
	if (is_digit(full_cmd[1]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(full_cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_shell.quit_status = 255;
		return (0);
	}
	else if (num > 2)
	{		
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_shell.quit_status = 1;
		return (1);
	}
	else
	{
		g_shell.quit_status = ft_atoi(full_cmd[1]);
		return (g_shell.quit_status);
	}
}
