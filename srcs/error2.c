/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:40:59 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/25 19:49:41 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	error_cd_relative_path(char *str)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_shell.quit_status = 1;
}

int	error_open_file(char *str)
{	
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (g_shell.quit_status = 1);
}

int	error_export(char *str, char *cmd)
{
	ft_putstr_fd("minishel: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	free(str);
	return (g_shell.quit_status = 1, 1);
}
