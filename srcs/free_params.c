/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 22:05:45 by nlibano-          #+#    #+#             */
/*   Updated: 2023/02/25 17:00:17 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	free_split(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	free_all(t_cmd *cmd)
{
printf("****liberando todo\n");
	if (cmd->cmd)
	{
	printf("1");	
		free_split(cmd->cmd);
	}
	if (cmd->cmd_line)
	{
			printf("2");	
		free(cmd->cmd_line);
	}
	if (cmd->readl)
	{
		printf("3");	
		free(cmd->readl);
	}
	if (cmd->pipe)
	{
			printf("4");	
		ft_pipelstclear(&(cmd->pipe));
	}
	if (cmd->redir)
	{
	printf("5");	
		ft_lstclear_redir(&(cmd->redir));
	}
}