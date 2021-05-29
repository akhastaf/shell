/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:40:21 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/29 15:34:46 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_backslash(char *str)
{
	int	i;
	int	j;
	int	sq;

	sq = 0;
	i = ft_strlen(str) - 1;
	j = 0;
	while (i >= 0)
	{
		if (str[i] == '\'' && !sq)
			sq = 0;
		else if (str[i] == '\'' && sq)
			sq = 0;
		if (str[i] == '\\' && !sq)
			j++;
		else if (str[i] != '\\')
			break ;
		i--;
	}
	return (j);
}
