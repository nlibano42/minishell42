/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:46:37 by jdasilva          #+#    #+#             */
/*   Updated: 2023/03/19 19:18:49 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*find_change_str(char *s, t_env *env)
{
	char	*aux;
	char	*val;

	if (s[0] == '$')
		aux = ft_substr(s, 1, ft_strlen(s) - 1);
	else
		aux = ft_substr(s, 0, ft_strlen(s));
	if (!ft_lstfind_env_val(env, aux))
		val = ft_strdup("");
	else
		val = ft_strdup(ft_lstfind_env_val(env, aux));
	free(aux);
	return (val);
}

int	find_str(char c, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (c == s[i])
			return (1);
	}
	return (0);
}

int	find_fin_str(char *s, int i)
{
	while (s[++i])
	{
		if (ft_isalnum(s[i]) == 0)
			return (i);
	}
	return (i);
}

int	join_split(t_cmd *cmd)
{
	int		i;

	free(cmd->cmd_line);
	cmd->cmd_line = ft_strdup("");
	i = -1;
	while (cmd->cmd[++i])
	{
		if (i != 0)
			cmd->cmd_line = ft_strjoin(cmd->cmd_line, ft_strdup("\n"));
		cmd->cmd_line = ft_strjoin(cmd->cmd_line, ft_strdup(cmd->cmd[i]));
	}	
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
