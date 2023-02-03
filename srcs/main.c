/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2022/12/15 04:04:37 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{	
	(void)argc;
	(void)argv;
	init_env(&(g_shell.env), env);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	while (1)
	{
		g_shell.readl = readline("Minishell $> ");
		add_history(g_shell.readl);
		if (!g_shell.readl)
		{
			printf("exit\n");
			//usar nuestro builtin de exit en lugar de exit()
			exit(g_shell.quit_status);
		}
		if (ft_strlen(g_shell.readl) > 0)
		{

		}
		//pdte liberar (t_env) env
	}
	return (0);
}