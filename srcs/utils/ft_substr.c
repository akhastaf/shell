/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:38:55 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 12:39:22 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = len;
	while (s[start] != '\0' && i <= j - 1 && ft_strlen(s) >= start)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
