/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:51:38 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/18 20:32:46 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	pwd(void)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	getcwd(pwd, PATH_MAX);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
}
