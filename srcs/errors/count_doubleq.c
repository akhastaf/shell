/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_doubleq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:45:29 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/13 15:26:00 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_doubleq(char *str)
{
	int	i;
	int	j;
	int	sq;
	int	q;

	i = 0;
	sq = 0;
	q = 0;
	j = 0;
	while (str[i])
	{
		ft_quotes(str, i, &q, &sq);
		if (str[i] == '"' && str[(i - 1 < 0 ? 0 : i - 1)] == '\\'
			&& count_backslash(ft_strndup(str, i)) % 2 == 0)
			j++;
		else if (!(str[i] == '\\' && str[i + 1] == '\\') && (str[i] == '"'
				&& !sq && str[(i - 1 < 0 ? 0 : i - 1)] != '\\'))
			j++;
		i++;
	}
	return (j);
}
