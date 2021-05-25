/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchrn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:26:09 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 12:27:02 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strnchrn(char *s, char *set)
{
	int	i;
	int	j;

	if (set[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_isstrnchr(char *s, char *set)
{
	int	i;
	int	j;

	if (set[0] == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
