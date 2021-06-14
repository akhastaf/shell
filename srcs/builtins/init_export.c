/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:17:49 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/13 11:30:00 by akhastaf         ###   ########.fr       */
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
