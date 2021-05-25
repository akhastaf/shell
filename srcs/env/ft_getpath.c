/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:34:35 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 20:10:42 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*trim_path(char *file)
{
	file = ft_putbackslash(file);
	file = ft_strremove(file, '\'');
	file = ft_strremove(file, '"');
	file = ft_strremove(file, '\\');
	return (file);
}

static char	*check_builtins(char *file, int *i)
{
	*i = 0;
	if (ft_is_empty(file) || file[0] == '.' || ft_isbuiltins(file)
		|| !ft_checkenv("PATH") || ft_strchr(file, '/'))
		return (file);
	return (file);
}

char	*ft_getpath(char *file)
{
	struct stat	sb;
	char		**path;
	char		*tmp;
	char		*filepath;
	int			i;

	file = trim_path(file);
	file = check_builtins(file, &i);
	path = ft_split(get_value(g_sh.env, "PATH"), ":");
	while (path[++i])
	{
		filepath = ft_strjoin(path[i], "/");
		tmp = filepath;
		filepath = ft_strjoin(filepath, file);
		free(tmp);
		if (!stat(filepath, &sb))
		{
			free(file);
			ft_delete_arg(path);
			return (filepath);
		}
		free(filepath);
	}
	ft_delete_arg(path);
	return (file);
}
