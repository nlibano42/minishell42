/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 05:01:42 by nlibano-          #+#    #+#             */
/*   Updated: 2022/12/15 05:01:45 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	ft_suppress_output(void)
{
	struct termios	config;

	if (tcgetattr(0, &config))
		perror("minishell: tcsetattr");
	config.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &config))
		perror("minishell: tcsetattr");
}

void	sighandler(int sig)
{
	ft_suppress_output();
	if (sig == SIGINT && g_shell.pid == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGINT && g_shell.pid == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_shell.pid = 0;
	}
	else if (sig == SIGQUIT && g_shell.pid == 1)
	{
		printf("Quit: 3\n");
		printf("\n");
		rl_redisplay();
	}
}
