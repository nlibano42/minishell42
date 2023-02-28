/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:04:10 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/28 20:32:30 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void echo (t_cmd *cmd)
{
	char	**line;
	int		i;
	int		j;
	int		flag;
	
	line = cmd->pipe->full_cmd;
	flag = 0;
	i = -1;
	while(line[++i])
		printf("cmd:%s\n", line[i]);
	i = 0;
	while(line[++i])
	{
		if(!ft_strcmp(line[i], "-n"))
			flag = 1;
		else if(line[i][1] == ' ')
			break;
		else if(line[i][0] == '-')
		{
			j = 0;
			while(line[i][++j])
			{
				if(line[i][j] == 'n')
				{
					flag = 1;
					continue;
				}
				else
				{
					flag = 0;
					break;
				}
			}
		}
	}
	if(flag == 1)
	{
		i --;
		while(line[i])
		{
			ft_putstr_fd(ft_deletequotes(line[i]), 1);
			if(line[i + 1])
				ft_putstr_fd(" ", 1);
			i ++;
		}
	}
	else
	{
		i = 0;
		while(line[++i])
		{
			ft_putstr_fd(ft_deletequotes(line[i]), 1);
			if(line[i + 1])
				ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
}