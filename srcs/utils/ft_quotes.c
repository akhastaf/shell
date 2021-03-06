/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:20:26 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/13 15:38:56 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quotes(char *c, int i, int *q, int *sq)
{
	if (c[i] == '"' && c[ternary(i - 1 > 0, i - 1, 0)] != '\\'
		&& !(*q) && !(*sq))
		*q = 1;
	else if (c[i] == '"' && c[ternary(i - 1 > 0, i - 1, 0)] != '\\' && *q)
		*q = 0;
	if (c[i] == '\'' && c[ternary(i - 1 > 0, i - 1, 0)] != '\\' && !(*sq)
		&& !(*q))
		*sq = 1;
	else if (c[i] == '\'' && c[ternary(i - 1 > 0, i - 1, 0)] != '\\' && *sq)
		*sq = 0;
}
