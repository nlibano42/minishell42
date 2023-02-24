/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/24 18:35:26 by jdasilva         ###   ########.fr       */
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
/* void redirections(char **input) //funciona  pero tenemos que saber cuando usarlo.
{
	int		i;
	int		j;

	i = -1;
	while (input[++i])
	{
		j = -1;
		while(input[i][++j])
		{
			if (!ft_strncmp(input[i], ">", 1))
			// se llama a la funcion correspondiente;
			if (!ft_strncmp(input[i], "<", 1))
			// se llama a la funcion correspondiente;
			if (!ft_strncmp(input[i], ">>", 2))
			// se llama a la funcion correspondiente;
			if (!ft_strncmp(input[i], "<<", 2))
			// se llama a la funcion correspondiente;;
		}
	}
} */

int	ft_access(char *input)
{
	int		i;
	char	**cmd_split;
	int		fd;

//	cmd_split = ft_split(input, ',');
	cmd_split = ft_split(input, '\n');
	fd = 0;
	i = -1;
	while (cmd_split[++i])
	{
		if (!ft_strncmp(cmd_split[i], ">", 1) && !access(cmd_split[i + 1], F_OK))
			fd = access(cmd_split[i + 1], W_OK);
		if (!ft_strncmp(cmd_split[i], "<", 1) && !access(cmd_split[i + 1], F_OK))
			fd = access(cmd_split[i + 1], R_OK );
		if (!ft_strncmp(cmd_split[i], ">>", 2) && !access(cmd_split[i + 1], F_OK))
			fd = access(cmd_split[i + 1], W_OK);
		if (fd == -1)
		{
			access_error(cmd_split[i + 1]);
			return (fd);
		}
	}
	return (fd);
}
