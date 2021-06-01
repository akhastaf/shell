/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:01 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/10 13:10:03 by akhastaf         ###   ########.fr       */
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
		if (ft_strchr(arg[i], ' ') || ft_strchr(arg[i], '=')
			|| ft_is_empty(arg[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier", arg[i]);
			ret = 1;
		}
		else
			ht_delone(g_sh.env, arg[i], ft_strlen(arg[i]), free);
		i++;
	}
	return (ret);
}
