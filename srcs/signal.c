/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 05:01:42 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/20 10:52:16 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_signal(void)
{
	ft_suppress_output(0);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

void	ft_suppress_output(int quit)
{
	struct termios	config;

	ft_bzero(&config, sizeof(config));
	tcgetattr(STDIN_FILENO, &config);
	if (quit == 0)
		config.c_lflag &= ~ECHOCTL;
	else
		config.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
}

void	show_readline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler(int sig)
{
	if (sig == SIGQUIT && g_shell.pid == 0)
		show_readline();
	else if (sig == SIGINT && g_shell.pid == 0)
	{
		printf("\n");
		show_readline();
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
