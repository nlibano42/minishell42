/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcontrol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/15 00:39:23 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	open_file(char *file, char *flag)
{
	int	fd;

	fd = -1;
	fd = open(file, flag);
	if (fd == -1)
	{
		g_shell.quit_status = 1; //mirar que numero debe devolver.
		exit (1);
	}
	return (fd);
}

/* redirections
*	s: readline (parse)
*/
void	redirections(char *input, char *file)
{
	int		i;
	char	**cmd_split;
	int		fd;
	char	*flag;

	cmd_split = ft_split(input, ',');
	i = -1;
	while (cmd_split[++i])
	{
		if (cmd_split[i] == '>')
			flag = "O_CREAT | O_TRUNC | O_WRONLY";
		if (cmd_split[i] == '<')
			flag = "O_RDONLY";
		if (cmd_split[i] == '>>')
			flag = "O_CREAT | O_APPEND | O_WRONLY";
		if (cmd_split[i] == '<<')
			flag = "O_RDONLY";
		fd = open_file(cmd_split[i + 1], flag);
		printf("%s\n", cmd_split[i]);
	}
}
