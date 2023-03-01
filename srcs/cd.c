/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:22:03 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/01 18:39:50 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	update_val(t_cmd *cmd, char *name, char *val)
{
	t_env	*env;

	env = cmd->env;
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			free(env->val);
			env->val = ft_strdup(val);
			break ;
		}
		env = env->next;
	}
}

void	cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	char	*tmp;
	int		i;

//	oldpwd = NULL;
	export_add(cmd, "OLDPWD");
	// cd (sin agurmentos)
	if (!cmd->pipe->full_cmd[1])
	{
		oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
		pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "HOME"));
		update_val(cmd, "OLDPWD", oldpwd);
		update_val(cmd, "PWD", pwd);
		chdir(pwd);
		free(oldpwd);
		free(pwd);
		return ;
	}
	//cd ..
	if (!ft_strcmp(cmd->pipe->full_cmd[1], ".."))
	{
		pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
		i = ft_strlen(pwd);
		while (pwd[--i])
		{
			if (pwd[i] == '/')
			{
				tmp = ft_substr(pwd, 0, i);
				update_val(cmd, "OLDPWD", pwd);
				update_val(cmd, "PWD", tmp);
				chdir(tmp);
				free(pwd);
				free(tmp);
				return ;	
			}
		}
		free(pwd);
		return ;
	}
	//cd -
	if (!ft_strcmp(cmd->pipe->full_cmd[1], "-"))
	{
		//TODO: si oldpwd esta vacio, error: bash: cd: OLDPWD not set
		if (ft_strlen(oldpwd) == 0)
		{
			ft_putstr_fd("error: bash: cd: OLDPWD not set\n",2);
			return;
		}
		oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "OLDPWD"));
		pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
		update_val(cmd, "PWD", oldpwd);
		update_val(cmd, "OLDPWD", pwd);
		chdir(oldpwd);
		ft_putstr_fd(oldpwd, 1);
		ft_putstr_fd("\n", 1);
		free(oldpwd);
		free(pwd);
		return ;
	}
	
	//TODO: si empieza por / es una ruta absoluta
}
