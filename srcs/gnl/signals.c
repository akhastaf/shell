/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:20:26 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 18:03:11 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_free(&g_sh.line);
		if (g_sh.tmp_line)
			ft_free(&g_sh.tmp_line);
		g_sh.tmp_hist = NULL;
		if (g_sh.pid == -1)
		{
			ft_putstr_fd("\n", 1);
			ft_putstr_fd("\033[0;32mMinishell$> \033[0m", 1);
		}
		else if (g_sh.pid)
			ft_putstr_fd("\n", 1);
	}
	if (sig == SIGQUIT && g_sh.pid != -1)
	{
		ft_putstr_fd("Quit: 3\n", 1);
	}
}
