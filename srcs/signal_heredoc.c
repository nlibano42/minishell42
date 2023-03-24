/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:03:30 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/23 20:17:51 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_signal_heredoc(void)
{
	ft_suppress_output(0);
	signal(SIGINT, sighandler_heredoc);
	signal(SIGQUIT, sighandler_heredoc);
}

void	sighandler_heredoc(int sig)
{
	if (sig == SIGINT && g_shell.pid == 2)
		exit(g_shell.quit_status = 1);
	if (sig == SIGQUIT && g_shell.pid == 2)
		rl_redisplay();
}
