/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 08:58:48 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 20:28:07 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_checkenv(char *var)
{
	char	*v;

	v = NULL;
	v = get_value(g_sh.env, var);
	if (v)
		return (1);
	return (0);
}
