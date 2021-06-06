/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:22:39 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 15:59:40 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_space(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	size_t	n;

	signe = 1;
	n = 0;
	i = skip_space((char *)str);
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			signe = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		n = n * 10 + str[i] - 48;
		if (n > 9223372036854775807)
		{
			if (signe > 0)
				return (1);
			return (0);
		}
		i++;
	}
	return ((int)(n * signe));
}
