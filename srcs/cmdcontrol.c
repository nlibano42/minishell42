/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/14 21:32:50 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_cmdcontrol(char *s)
{
	int i;
	char ** cmd_split;
	int fd;

	cmd_split = ft_split(s, ',');
	i = -1;
	while(cmd_split[++i])
	{
		if(cmd_split[i] == '>')
		{
			fd = open(cmd_split[i + 1], O_CREAT | O_TRUNC | O_WRONLY);
			if(fd == -1 )
				return (-1);
		}
		if(cmd_split[i] == '<')
		{
			fd = open(cmd_split[i + i], O_RDONLY);
			if(fd == -1)
				return (-1);
		}
		if(cmd_split[i] == '>>')
		{
			fd = open(cmd_split[i + i], O_CREAT | O_APPEND | O_WRONLY);
			if(fd == -1)
				return (-1);
		}
		if(cmd_split[i] == '<<')
		{
			fd = open(cmd_split[i + i], O_RDONLY);
			if(fd == -1)
				return(-1);
		}
		printf("%s\n", cmd_split[i]);
	}
	
}