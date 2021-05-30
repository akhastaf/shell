/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:06:56 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 12:12:27 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*s;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	while (*s2)
	{
		*(s + i) = *s2;
		s2++;
		i++;
	}
	*(s + i) = '\0';
	return (s);
}