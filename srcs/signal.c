/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 05:01:42 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/25 15:53:43 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
#include <termios.h>

void	ft_signal(void)
{	
	ft_suppress_output();
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}

void	ft_suppress_output(void)
{
	struct termios	config;

	if (tcgetattr(0, &config))
		perror("minishell: tcsetattr");
		config.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &config))
		perror("minishell: tcsetattr");
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
	{
printf("soy el padre y sig = SIGOUT\n");
		show_readline();
	}
	else if (sig == SIGINT && g_shell.pid == 0)
	{
printf("soy el padre y sig = SIGINT\n");
		printf("\n");
		show_readline();
	}
	if (sig == SIGINT && g_shell.pid == 1)
	{
printf("soy el hijo y sig = SIGINT\n");
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_shell.pid = 0;
	}
	else if (sig == SIGQUIT && g_shell.pid == 1)
	{
printf("soy el hijo y sig = SIGOUT\n");
		printf("Quit: 3\n");
		printf("\n");
		rl_redisplay();
	}
}
