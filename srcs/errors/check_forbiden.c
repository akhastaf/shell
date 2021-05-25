/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_forbiden.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:41:29 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 20:12:18 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_forbiden(void)
{
	if (ft_strnchr(g_sh.line, "<<"))
		return (7);
	if (ft_strnchr(g_sh.line, ">>>"))
		return (8);
	return (0);
}
