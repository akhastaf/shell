/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:17:49 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 19:29:35 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_export(t_kv *e, char **tmp, t_ex *ex)
{
	e->v = NULL;
	*tmp = NULL;
	ex->n = 0;
	ex->ret = 0;
}
