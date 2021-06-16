/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:17:49 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/16 15:46:09 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_export(char **tmp, t_ex *ex)
{
	ex->v = NULL;
	*tmp = NULL;
	ex->n = 0;
	ex->ret = 0;
}

void	free_ex(char *k, char *v)
{
	free(k);
	free(v);
}

void	printe(char *v, char *data)
{
	ft_putstr_fd("declare -x ", 1);
	if (v)
	{
		ft_putstr_fd(data, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(v, 1);
	}
	else
		ft_putendl_fd(data, 1);
}
