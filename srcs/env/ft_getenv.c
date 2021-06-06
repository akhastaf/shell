/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:35:29 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 12:41:29 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char *var)
{
	char	*v;

	v = get_value(g_sh.env, var);
	if (v)
		return (ft_strdup(v));
	if (!ft_strcmp(var, "PWD") && g_sh.pwd)
		return (ft_strdup(g_sh.pwd));
	if (!ft_strcmp(var, "OLDPWD") && g_sh.oldpwd)
		return (ft_strdup(g_sh.oldpwd));
	return (NULL);
}
