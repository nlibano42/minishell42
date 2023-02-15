/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/15 20:09:22 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	open_file(char *file, char flag)
{
	int	fd;

	fd = -1;
	if (flag == 'r')
		fd = open(file, O_RDONLY);
	else if (flag == 'w')
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC);
	else if (flag == 'a')
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		g_shell.quit_status = 1; //mirar que numero debe devolver.
	return (fd);
}

/* redirections
*	s: readline (parse)
*/
int	redirections(char *input) //funciona  pero tenemos que saber cuando usarlo.
{
	int		i;
	char	**cmd_split;
	int		fd;

	cmd_split = ft_split(input, ',');
	fd = 0;
	i = -1;
	while (cmd_split[++i])
	{
		if (!ft_strncmp(cmd_split[i], ">", 1))
			fd = open_file(cmd_split[i + 1], 'w');
		if (!ft_strncmp(cmd_split[i], "<", 1))
			fd = open_file(cmd_split[i + 1], 'r');
		if (!ft_strncmp(cmd_split[i], ">>", 2))
			fd = open_file(cmd_split[i + 1], 'a');
		if (!ft_strncmp(cmd_split[i], "<<", 2))
			fd = open_file(cmd_split[i + 1], 'r');
		if(fd == -1)
		{
			printf("entra\n");
			break ;
		}
		//fd = open_file(cmd_split[i + 1], flag);
		printf("%s\n", cmd_split[i]);
	}
	return (fd);
}

int ft_access(char *input)
{
	int i;
	char **cmd_split;
	int fd;

	cmd_split = ft_split(input, ',');
	fd = 0;
	i = -1;
	while (cmd_split[++i])
	{
		
		if (!ft_strncmp(cmd_split[i], ">", 1))
			fd = access(cmd_split[i + 1], W_OK);
		if (!ft_strncmp(cmd_split[i], "<", 1))
			fd = access(cmd_split[i + 1], R_OK);
		if (!ft_strncmp(cmd_split[i], ">>", 2))
			fd = access(cmd_split[i + 1], W_OK);
		if (!ft_strncmp(cmd_split[i], "<<", 2))
			fd = open_file(cmd_split[i + 1], R_OK);
		if(fd == -1)
			return(fd);
		printf("fd:%d\n", fd);
		printf("%s\n", cmd_split[i]);
	}
	return (fd);
}