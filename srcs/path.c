/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:51:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/22 00:10:26 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**tab_env(t_env *env)
{
	char **tab;
	int	i;
	char *s;

	i = 1;
	while(env)
	{
		i++;
		env = env->next;
	}
	tab = (char **)malloc((sizeof(char *) * i + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while(env)
	{
		s = ft_strjoin(ft_strdup(env->name), ft_strdup("="));
		s = ft_strjoin(s, ft_strdup(env->val));
		tab[++i] = s;
		env = env->next;
	}
	tab[i + 1] = NULL;
	return (tab);
}

/*void get_path(char *cmd, t_env *env)
{
	int i;
	char *path;
	char **sp;
	char **sp_cmd;
	char **char_env;

	char_env = tab_env(env);
	sp_cmd = ft_split(cmd, '\n');
	path = ft_lstfind_env_val(env, "PATH");
	sp = ft_split(path, ':');
	i = -1;
	while(sp[++i])
	{
	
		sp[i] = ft_strjoin(sp[i], ft_strdup("/"));
		sp[i] = ft_strjoin(sp[i], ft_strdup(sp_cmd[0]));
		printf("%s\n", sp[i]);
		if(access(sp[i], F_OK) == 0)
		{
			printf("....entra\n");
			printf("cmd: %s\n", cmd);
			execve(sp[i], &cmd, char_env); // hay que averiguar como omitir el null
			break ;
		}
	}
	free_split(sp_cmd);
	free_split(sp);
	free_split(char_env);
}*/