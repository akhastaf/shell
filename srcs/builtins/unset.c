/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:01 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/07 18:32:26 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins_unset(char **arg)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "PWD"))
			g_sh.is_pwd = 0;
		if (!ft_strcmp(arg[i], "OLDPWD"))
			g_sh.is_oldpwd = 0;
		if (ft_strchr(arg[i], ' ') || !ft_isvalidarg(arg[i])
			|| ft_is_empty(arg[i]) || ft_strchr(arg[i], '+'))
		{
			ft_puterror("minishell: unset: `", arg[i],
				"': not a valid identifier");
			ret = 1;
		}
		else if (is_key(g_sh.env, arg[i]))
			ht_delone(g_sh.env, arg[i], free);
		i++;
	}
	return (ret);
}
