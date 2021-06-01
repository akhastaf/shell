/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:24:47 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/26 15:51:19 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(void)
{
	t_list	*tmp;

	tmp = g_sh.pipeline;
	while (tmp)
	{
		process_pipeline(((t_pipeline *)tmp->data));
		open_pipes(((t_pipeline *)tmp->data));
		if (((t_pipeline *)tmp->data)->cmd)
			magic_box(tmp->data);
		reset_std();
		if (!tmp->next)
			ft_set_lstcmd(((t_pipeline *)tmp->data)->cmd);
		tmp = tmp->next;
	}
}
