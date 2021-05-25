/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:09 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 16:35:48 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD");
	if (!oldpwd)
		ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
	return (oldpwd);
}

static int	missing_arg(char *arg, char **str, char **oldpwd)
{
	*oldpwd = ft_getenv("PWD");
	if (!*oldpwd)
		*oldpwd = ft_strdup("");
	if (!arg)
	{
		*str = ft_getenv("HOME");
		if (!(*str))
		{
			ft_putendl_fd("minishell: cd: HOME not set", 1);
			return (1);
		}
	}
	else if (*str[0] == '\0' && *oldpwd)
	{
		ht_add(g_sh.env, ft_strdup("OLDPWD"), *oldpwd, 6, free);
		return (1);
	}
	return (0);
}

static int	get_home(char **str)
{
	if (!ft_strcmp(*str, "-"))
	{
		free(*str);
		*str = ft_getenv("OLDPWD");
		if (*str)
			ft_putendl_fd(*str, 1);
		else
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
			return (1);
		}
	}
	return (0);
}

void	set_pwd(char *str)
{
	char	*pwd;
	char	*tmp;

	 pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("cd: error retrieving current directory: getcwd: cannot \
				access parent directories: %s\n", strerror(errno));
		pwd = ft_getenv("PWD");
		pwd = ft_strappend(pwd, '/');
		tmp = pwd;
		pwd = ft_strjoin(pwd, str);
		free(tmp);
	}
	ht_add(g_sh.env, ft_strdup("PWD"), pwd, 3, free);
}

int	builtins_cd(char **arg)
{
	char	*oldpwd;
	char	*pwd;
	char	*str;
	char	*tmp;

	str = ft_strdup(arg[1]);
	if (missing_arg(arg[1], &str, &oldpwd))
		return (1);
	if (get_home(&str))
		return (1);
	if (!chdir(str))
	{
		set_pwd(str);
		if (oldpwd)
			ht_add(g_sh.env, ft_strdup("OLDPWD"), oldpwd, 6, free);
	}
	else
	{
		printf("minishell: cd: %s : %s\n", str, strerror(errno));
		if (!arg[1])
			free(str);
		return (1);
	}
	free(str);
	return (0);
}
