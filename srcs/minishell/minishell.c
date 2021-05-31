/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:06:58 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/26 15:48:27 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_loop(void)
{
	char	*error;

	error = 0;
	while (1)
	{
		ft_putstr_fd("\033[0;32mMinishell$> \033[0m", 1);
		tcgetattr(0, &g_sh.tc.init);
		gnl_term();
		tcsetattr(0, TCSANOW, &g_sh.tc.init);
		error = check_syntax();
		if (error)
		{
			printf("%s\n", error);
			g_sh.status = 258;
		}
		else
		{
			init_pipeline();
			execute();
			ft_lstclear(&(g_sh.pipeline), delete_pipe);
		}
		free(g_sh.line);
		g_sh.line = NULL;
		g_sh.pid = 0;
		g_sh.error = 0;
	}
}

void	print_pipeline(void)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = g_sh.pipeline;
	while (tmp)
	{
		printf("%d\t\t|%s|\n", i, ((t_pipeline *)tmp->data)->str);
		tmp = tmp->next;
		i++;
	}
}
