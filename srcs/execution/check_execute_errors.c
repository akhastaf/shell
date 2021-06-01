/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execute_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:47:19 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 15:54:26 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	is_dir(char *bin, char **path, DIR *dir)
{
	ft_puterror("minishell: ", bin, ": is a directory");
	closedir(dir);
	if (*path)
		free(*path);
	exit(126);
}

static void	not_dir(char *bin, char **path)
{
	ft_puterror("minishell: ", bin, ": No such file or directory");
	if (*path)
		free(*path);
	exit(127);
}

static void	cmd_not_found(char *bin, char **path)
{
	ft_puterror("minishell: ", bin, ": command not found");
	if (*path)
		free(*path);
	exit(127);
}

static void	access_deined(char *bin, char **path)
{
	ft_puterror("minishell: ", bin, ": Permission denied");
	if (*path)
		free(*path);
	exit(126);
}

void	check_execute_errors(t_cmd *cmd, int err)
{
	struct stat	sb;
	char		*path;
	char		*spath;
	DIR			*dir;

	path = ft_getenv("PATH");
	if (!ft_strchr(cmd->path, '/') && (!path || ft_is_empty(path)))
		spath = ft_strjoin("./", cmd->path);
	else if (ft_strchr(cmd->path, '/'))
		spath = cmd->path;
	dir = opendir(spath);
	if ((dir && (ft_strchr(cmd->path, '/') || !path || ft_is_empty(path)))
		|| (errno == 13 && (ft_strchr(cmd->path, '/') || !path
				|| ft_is_empty(path))))
		is_dir(cmd->path, &path, dir);
	else if ((!path || ft_is_empty(path)) && stat(spath, &sb))
		not_dir(cmd->path, &path);
	else if (err == 2 || dir)
		cmd_not_found(cmd->path, &path);
	else if (err != 8)
		access_deined(cmd->path, &path);
}
