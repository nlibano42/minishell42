/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdasilva <jdasilva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:51:55 by jdasilva          #+#    #+#             */
/*   Updated: 2023/02/20 21:18:13 by jdasilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**tab_env(t_env *env)
{
	char **tab;
	int	i;
	char *s;
	char *s1;

	i = 1;
	while(env)
	{
		i++;
		env = env->next;
	}
	tab =(char **)malloc((sizeof(char *) * i + 1));
	if(!tab)
		return (NULL);
	i = -1;
	while(env)
	{
		s = ft_strjoin(env->name, ft_strdup("="));
		s1 = ft_strjoin(s, env->val);
		tab[++i] = ft_strdup(s1);
		free(s);
		free(s1);
		env = env->next;
	}
	tab[ i + 1] = NULL;
	return(tab);
}

void get_path(char *cmd, t_env *env)
{
	int i;
	char *path;
	char **sp;
	char **sp_cmd;
	char **char_env;

	char_env = tab_env(env);
	sp_cmd = ft_split(cmd, ' ');
	path = ft_lstfind_env_val(env, "PATH");
	sp = ft_split(path, ':');
	i = -1;
	while(sp[++i])
	{
		sp[i] = ft_strjoin(sp[i], ft_strdup("/"));
		sp[i] = ft_strjoin(sp[i], ft_strdup(sp_cmd[0]));
		if(access(sp[i], F_OK) == 0)
		{
			execve(sp[i], &cmd, char_env); // hay que averiguar como omitir el null
				
		}
	}
}