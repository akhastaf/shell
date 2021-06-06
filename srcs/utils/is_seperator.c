/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_seperator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:13:23 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 20:13:24 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_seperator(char *s, int i, char *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == s[i] && (s[ternary(i - 1 < 0, 1, i - 1)] != '\\'
				|| !is_specialcar(s[i])))
			return (1);
		j++;
	}
	return (0);
}
