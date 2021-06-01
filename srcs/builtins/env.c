/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:16 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 18:47:47 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_lastcmd(void)
{
	int		i;
	int		l;
	char	*lstcmd;

	i = 1;
	lstcmd = ft_getpath(ft_strdup("ENV"), 0);
	l = ft_strlen(lstcmd);
	while (i < 4)
	{
		lstcmd[l - i] = ft_tolower(lstcmd[l - i]);
		i++;
	}
	ht_replace(g_sh.env, ft_strdup("_"), lstcmd, 1);
}

int	builtins_env(char **arg)
{
	int		i;
	t_list	*tmp;

	set_lastcmd();
	i = 0;
	while (i < g_sh.env->lenght)
	{
		tmp = g_sh.env->backets[i];
		while (tmp && ((t_key_value *)tmp->data)->value)
		{
			if (ft_strcmp(((t_key_value *)tmp->data)->key, "_"))
			{
				printf("%s=%s\n", (char *)((t_key_value *)tmp->data)->key,
					(char*)((t_key_value *)tmp->data)->value);
			}
			tmp = tmp->next;
		}
		i++;
	}
	printf("_=%s\n", get_value(g_sh.env, "_"));
	return (0);
}
