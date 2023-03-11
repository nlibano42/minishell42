/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:02:29 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/11 19:46:23 by nlibano-         ###   ########.fr       */
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
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 'a')
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		g_shell.quit_status = 1; //mirar que numero debe devolver.
	return (fd);
}

int	redirections(t_pipe *pipes)
{
	if(pipes->infile == -1 || pipes->outfile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(pipes->redir->file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (g_shell.quit_status = 1);
	}
	if (pipes->infile == 0 && pipes->outfile == 0)
		return  (0);
	if (!ft_strcmp(pipes->redir->type, "read"))
	{
		dup2(pipes->infile, STDIN_FILENO);
		//close(pipes->infile);
	}
	return (0);
}

int	ft_access(char *input)
{
	int		i;
	char	**cmd_split;
	int		fd;

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
