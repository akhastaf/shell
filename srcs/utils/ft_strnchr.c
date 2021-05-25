/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:14:41 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 12:25:36 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init(size_t *i, size_t *j, int *q, int *sq)
{
	*i = 0;
	*j = 0;
	*q = 0;
	*sq = 0;
}

char	*ft_strnchr(char *s, char *set)
{
	size_t	i;
	size_t	j;
	int		q;
	int		sq;

	if (set[0] == '\0')
		return (0);
	init(&i, &j, &q, &sq);
	while (s[i + j])
	{
		ft_quotes(s[i], &q, &sq);
		while (s[i + j] && s[i + j] == set[j])
		{
			j++;
			if (set[j] == '\0' && !sq && !q)
				return (s + i);
			while (s[i + j] == ' ' || s[i + j] == '\t')
				i++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
