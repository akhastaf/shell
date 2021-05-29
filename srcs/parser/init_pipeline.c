/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:44:38 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/26 17:54:25 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipeline(void)
{
	char		**pipeline;
	t_pipeline	*p;
	int			i;

	if (g_sh.line)
	{
		pipeline = ft_split(g_sh.line, ";");
		i = 0;
		while (pipeline[i])
		{
			p = malloc(sizeof(t_pipeline));
			if (!p)
				return ;
			p->str = pipeline[i];
			p->cmd = NULL;
			ft_lstadd_back(&g_sh.pipeline, ft_lstnew(p));
			i++;
		}
		free(pipeline);
	}
}
