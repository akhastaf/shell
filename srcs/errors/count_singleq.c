/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_singleq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:46:41 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/16 17:47:09 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     count_singleq(char *str)
{
	int i;
	int j;
	int q;
	int sq;

	i = 0;
	q = 0;
	sq = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && !q && !sq)
			q = 1;
		else if (str[i] == '"' && q)
			q = 0;
		if (str[i] == '\'' && !sq && !q)
			sq = 1;
		else if (str[i] == '\'' && sq)
			sq = 0;
		if (str[i] == '\'' && !q)
			j++;
		i++;
	}
	return j;
}