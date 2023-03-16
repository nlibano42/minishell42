/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlibano- <nlibano-@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:22:03 by nlibano-          #+#    #+#             */
/*   Updated: 2023/03/16 23:48:08 by nlibano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	cd_no_argumnets(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
	pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "HOME"));
	update_val(cmd, "OLDPWD", oldpwd);
	update_val(cmd, "PWD", pwd);
	chdir(pwd);
	free(oldpwd);
	free(pwd);
}

void	cd_up_dir(t_cmd *cmd)
{
	char	*tmp;
	char	*pwd;
	int		i;

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
}

void	cd_undo(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strdup(ft_lstfind_env_val(cmd->env, "OLDPWD"));
	if (ft_strlen(oldpwd) == 0)
	{
		ft_putstr_fd("error: bash: cd: OLDPWD not set\n", 2);
		return ;
	}
	pwd = ft_strdup(ft_lstfind_env_val(cmd->env, "PWD"));
	update_val(cmd, "PWD", oldpwd);
	update_val(cmd, "OLDPWD", pwd);
	chdir(oldpwd);
	ft_putstr_fd(oldpwd, 1);
	ft_putstr_fd("\n", 1);
	free(oldpwd);
	free(pwd);
}

void	cd(t_cmd *cmd, t_pipe *pipex)
{
	if (ft_strlen(ft_lstfind_env_val(cmd->env, "OLDPWD")) == 0)
		export_add(cmd, "OLDPWD");
	if (!pipex->full_cmd[1] || !ft_strcmp(pipex->full_cmd[1], "~"))
		cd_no_argumnets(cmd);
	else if (!ft_strcmp(pipex->full_cmd[1], ".."))
		cd_up_dir(cmd);
	else if (!ft_strcmp(pipex->full_cmd[1], "-"))
		cd_undo(cmd);
	else
	{
		if (pipex->full_cmd[1][0] == '/')
			cd_absolute_path(cmd, pipex);
		else
			cd_relative_path(cmd, pipex);
	}
	//TODO: cuando sacamos el error hay que expandir ~
}
