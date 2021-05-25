/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:36:00 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 11:37:44 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_getsize(int n)
{
	int				i;
	unsigned int	nb;

	i = 0;
	nb = n;
	if (n < 0)
	{
		nb = -n;
		i++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;

	nb = n;
	i = ft_getsize(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
	}
	i--;
	while (nb >= 10 && i >= 0)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	if (nb <= 9)
		str[i] = nb + '0';
	return (str);
}
