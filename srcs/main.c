/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 09:48:08 by nlibano-          #+#    #+#             */
/*   Updated: 2022/12/02 16:25:08 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_prompt_line(t_shell *shell)
{
	shell->read_line = readline(
}

void	init_shell(t_shell *shell)
{
	shell.read_line = NULL;
}

int	main(int argc, char **argv, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;

	init_shell(&shell);	
	while (1)
	{
		get_prompt_line(&shell);
	}
	return (0);
}
