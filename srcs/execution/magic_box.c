/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:48:51 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/16 14:26:27 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_nonpipeline(t_list **tmp)
{
	if (!g_sh.error && !ft_is_empty(((t_cmd *)(*tmp)->data)->path)
		&& ft_isbuiltins(((t_cmd *)(*tmp)->data)->path))
	{
		setup_redirection((*tmp)->data);
		if (!g_sh.error)
			execute_builtins(((t_cmd *)(*tmp)->data)->path,
				((t_cmd *)(*tmp)->data)->arg);
		*tmp = (*tmp)->next;
	}
}

static	void	execute_nonbuiltins(t_list *p)
{
	if (!g_sh.error && (((t_cmd *)p->data)->path)
		&& execve(((t_cmd *)p->data)->path,
			((t_cmd *)p->data)->arg, ht_totable(g_sh.env)))
		check_execute_errors(p->data, errno);
}

static void	execute_pipeline(t_list *p)
{
	while (p)
	{
		g_sh.is_pipe = 1;
		g_sh.pid = fork();
		if (g_sh.pid < 0)
			return ;
		if (!g_sh.pid)
		{
			setup_pipe(p);
			setup_redirection(p->data);
			if (!g_sh.error && !ft_is_empty(((t_cmd *)p->data)->path)
				&& ft_isbuiltins(((t_cmd *)p->data)->path))
			{
				execute_builtins(((t_cmd *)p->data)->path,
					((t_cmd *)p->data)->arg);
				exit(g_sh.status);
			}
			execute_nonbuiltins(p);
			exit(0);
		}
		close(((t_cmd *)p->data)->pipe[1]);
		if (p->prev)
			close(((t_cmd *)p->prev->data)->pipe[0]);
		p = p->next;
	}
}

void	magic_box(t_pipeline *p)
{
	t_list	*tmp;

	tmp = p->cmd;
	if (!(tmp->next))
		execute_nonpipeline(&tmp);
	execute_pipeline(tmp);
	g_sh.is_pipe = 0;
	close_pipe(p);
	waitpid(g_sh.pid, &g_sh.status, 0);
	if (g_sh.pid > 0 && (g_sh.status) && WIFSIGNALED(g_sh.status))
		g_sh.status = 128 + WTERMSIG(g_sh.status);
	else if (g_sh.pid > 0)
		g_sh.status = WEXITSTATUS(g_sh.status);
	while (wait(NULL) > 0)
		;
}
