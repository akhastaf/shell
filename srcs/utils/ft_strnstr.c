/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:30:50 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 12:31:26 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*to_find;

	str = (char *)haystack;
	to_find = (char *)needle;
	if (to_find[0] == '\0')
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (str[i + j] != '\0' && i < len)
	{
		while (str[i + j] == to_find[j] && i + j < len)
		{
			j++;
			if (to_find[j] == '\0')
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
