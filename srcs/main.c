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
	init_env(&(g_shell.envi), env);
//	signal(SIGINT, sighandler);
//	signal(SIGQUIT, sighandler);
	while (1)
	{
//		g_shell.readl = readline("Minishell $> ");
//		add_history(g_shell.readl);
	}
	return (0);
}