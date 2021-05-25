/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:08:40 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 19:55:55 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_pipe(t_list *cmd)
{
	if (cmd->next)
	{
		dup2(((t_cmd *)cmd->data)->pipe[1], 1);
		close(((t_cmd *)cmd->data)->pipe[1]);
		close(((t_cmd *)cmd->data)->pipe[0]);
	}
	if (cmd->prev && cmd->next)
	{
		dup2(((t_cmd *)cmd->prev->data)->pipe[0], 0);
		close(((t_cmd *)cmd->prev->data)->pipe[0]);
		close(((t_cmd *)cmd->prev->data)->pipe[1]);
	}
	if (cmd->prev && !cmd->next)
	{
		dup2(((t_cmd *)cmd->prev->data)->pipe[0], 0);
		close(((t_cmd *)cmd->prev->data)->pipe[0]);
	}
}

void	reset_std(void)
{
	dup2(g_sh.in, 0);
	dup2(g_sh.out, 1);
}

void	close_pipe(t_pipeline *p)
{
	t_list	*tmp;

	tmp = p->cmd;
	while (tmp)
	{
		if (tmp->next)
		{
			close(((t_cmd *)tmp->data)->pipe[0]);
			close(((t_cmd *)tmp->data)->pipe[1]);
		}
		tmp = tmp->next;
	}
}

void	open_pipes(t_pipeline *p)
{
	t_list	*tmp;
	int		l;

	tmp = p->cmd;
	l = ft_lstsize(tmp);
	while (tmp && l >= 2)
	{
		if (tmp->next)
			pipe(((t_cmd *)tmp->data)->pipe);
		tmp = tmp->next;
	}
}
