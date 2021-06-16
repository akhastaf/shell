/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:16 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/16 15:35:51 by akhastaf         ###   ########.fr       */
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
	ht_replace(g_sh.env, ft_strdup("_"), lstcmd);
}

int	builtins_env(char **arg)
{
	size_t	i;
	t_list	*tmp;

	(void)arg;
	set_lastcmd();
	i = 0;
	while (i < g_sh.env->lenght)
	{
		tmp = g_sh.env->backets[i];
		while (tmp && ((t_key_value *)tmp->data)->value)
		{
			if (ft_strcmp(((t_key_value *)tmp->data)->key, "_"))
			{
				ft_putstr_fd((char *)((t_key_value *)tmp->data)->key, 1);
				ft_putstr_fd("=", 1);
				ft_putendl_fd((char *)((t_key_value *)tmp->data)->value, 1);
			}
			tmp = tmp->next;
		}
		i++;
	}
	printf("_=%s\n", get_value(g_sh.env, "_"));
	return (0);
}
