/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tilde.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:08:13 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 15:57:35 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*check_plus(char *s, char *line, int i)
{
	char	*tmp;
	char	*tmp1;

	if (s[i + 1] == '+' && ft_checkenv("PWD")
		&& (ft_is_space(s[i + 2]) || s[i + 2] == 0))
	{
		tmp = ft_getenv("PWD");
		tmp1 = ft_strjoin(line, tmp);
		free(tmp);
		return (tmp1);
	}
	return (NULL);
}

static char	*check_minus(char *s, char *line, int i)
{
	char	*tmp;
	char	*tmp1;

	if (s[i + 1] == '-' && ft_checkenv("OLDPWD")
		&& (ft_is_space(s[i + 2]) || s[i + 2] == 0))
	{
		tmp = ft_getenv("OLDPWD");
		tmp1 = ft_strjoin(line, tmp);
		free(tmp);
		return (tmp1);
	}
	return (NULL);
}

static char	*check_home(char *line)
{
	char	*tmp;
	char	*tmp1;

	if (ft_checkenv("HOME"))
	{
		tmp = ft_getenv("HOME");
		tmp1 = ft_strjoin(line, tmp);
		free(tmp);
		return (tmp1);
	}
	else
		return (ft_strjoin(line, g_sh.home));
}

char	*ft_tilde(char *s, char *line, int i)
{
	char	*tmp;

	tmp = check_plus(s, line, i);
	if (tmp)
		return (tmp);
	tmp = check_minus(s, line, i);
	if (tmp)
		return (tmp);
	if (s[i + 1] == '+' || s[i + 1] == '-')
	{
		line = ft_strappend(line, '~');
		line = ft_strappend(line, s[i + 1]);
	}
	else
		return (check_home(line));
	return (line);
}
