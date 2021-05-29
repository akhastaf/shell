/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:42:12 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/28 17:44:37 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	increment_shlvl(void)
{
	int		value;
	char	*env;
	char	*v;

	env = ft_getenv("SHLVL");
	if (env)
		value = ft_atoll(env);
	else
		value = 0;
	free(env);
	if (value >= 2147483647)
		value = -1;
	if (value >= 200000)
	{
		printf("minishell: warning: shell level (%d) too high, \
				resetting to 1", value + 1);
		value = 0;
	}
	else if (value < 0)
		value = -1;
	v = ft_itoa(value + 1);
	ht_replace(g_sh.env, ft_strdup("SHLVL"), v, 5, free);
}
