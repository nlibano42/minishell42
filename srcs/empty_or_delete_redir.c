/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_or_delete_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:28:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/25 16:40:40 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**fill_empty(void)
{
	char	**s;

	s = (char **)malloc(sizeof(char *) * 2);
	if (!s)
		return (NULL);
	s[0] = ft_strdup("");
	s[1] = NULL;
	return (s);
}

int	save_empty(t_cmd *cmd)
{
	t_pipe	*pipe;

	pipe = ft_newpipe();
	pipe->full_cmd = fill_empty();
	pipe->path = ft_strdup("");
	ft_pipeadd_back(&(cmd->pipe), pipe);
	return (0);
}

char	**delete_redirection(char *sp, int *len)
{
	int		i;
	int		j;
	char	**res;
	char	**s;

	s = ft_split(sp, '\n');
	res = (char **)malloc(sizeof(char *) * (delete_redir_len(s, len) + 1));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], "<<") || \
			!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>"))
		{
			i++;
			continue ;
		}
		res[j] = ft_strtrim(s[i], " ");
		j++;
	}
	res[j] = NULL;
	free_split(s);
	return (res);
}

int	delete_redir_len(char **s, int *len)
{
	int	i;

	*len = 0;
	i = -1;
	while (s[++i])
	{
		if (!ft_strcmp(s[i], "<") || !ft_strcmp(s[i], "<<") || \
			!ft_strcmp(s[i], ">") || !ft_strcmp(s[i], ">>"))
		{
			i++;
			continue ;
		}
		(*len)++;
	}
	return (*len);
}

int	init_redir_size(t_pipe **pipe, char **sp)
{
	if ((*pipe)->num_redi > 0)
	{
		(*pipe)->redir = malloc(sizeof(t_redir) * ((*pipe)->num_redi + 1));
		if (!(*pipe)->redir)
		{
			ft_pipedelone(*pipe);
			free_split(sp);
			return (1);
		}
	}
	return (0);
}
