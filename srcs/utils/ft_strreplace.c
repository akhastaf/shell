/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:33:44 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 12:33:58 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strrepace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i++;
			while (str[i] != 34 && str[i] != 39)
				i++;
		}
		if (str[i] == ' ')
			str[i] = ',';
		i++;
	}
	return (str);
}
