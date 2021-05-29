/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execute_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:47:19 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/29 16:42:25 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_execute_errors(t_cmd *cmd, int err)
{
	struct stat	sb;
	char		*path;
	char		*spath;
	DIR			*dir;

	path = ft_getenv("PATH");
	if (!ft_strchr(cmd->path, '/') && (!path || ft_is_empty(path)))
		spath = ft_strjoin("./", cmd->path);
	dir = opendir(spath);
	if ((dir && (ft_strchr(cmd->path, '/') || !path || ft_is_empty(path)))
		|| (errno == 13 && (ft_strchr(cmd->path, '/') || !path
				|| ft_is_empty(path))))
	{
		ft_puterror("minishell: ", cmd->path, ": is a directory");
		closedir(dir);
		if (path)
			free(path);
		exit(126);
	}
	else if ((!path || ft_is_empty(path)) && stat(spath, &sb))
	{
		ft_puterror("minishell: ", cmd->path, ": No such file or directory");
		if (path)
			free(path);
		exit(127);
	}
	else if (err == 2 || dir)
	{
		ft_puterror("minishell: ", cmd->path, ": command not found");
		if (path)
			free(path);
		exit(127);
	}
	else if (err != 8)
	{
		ft_puterror("minishell: ", cmd->path, ": Permission denied");
		if (path)
			free(path);
		exit(126);
	}
}
