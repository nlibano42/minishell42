/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 22:05:45 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/12 15:16:37 by nlibano-         ###   ########.fr       */
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
	if (cmd->cmd)
		free_split(cmd->cmd);
	if (cmd->cmd_line)
		free(cmd->cmd_line);
	if (cmd->readl)
		free(cmd->readl);
	if (cmd->pipe)
		ft_pipelstclear(&(cmd->pipe));
//	if (cmd->redir)
//		ft_lstclear_redir(&(cmd->redir));
}
