/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 04:04:34 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/06 18:26:51 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{	
	(void)argc;
	(void)argv;
	init_env(&(g_shell.env), env);
	ft_suppress_output();
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
			if(linecontrol(g_shell.readl))
			{
				
			}
		}
		//pdte liberar (t_env) env
	}
	return (0);
}