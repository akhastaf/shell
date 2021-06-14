/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:42:41 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/13 15:33:39 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strappend(char *str, char c)
{
	char	*s;
	int		l;
	int		i;

	if (!str)
	{
		s = malloc(sizeof(char) * 2);
		if (!s)
			return (NULL);
		s[0] = c;
		s[1] = 0;
		return (s);
	}
	l = ft_strlen(str);
	s = malloc(sizeof(char) * (l + 2));
	if (!s)
		return (NULL);
	i = -1;
	while (++i < l)
		s[i] = str[i];
	s[i++] = c;
	s[i] = 0;
	free(str);
	return (s);
}
