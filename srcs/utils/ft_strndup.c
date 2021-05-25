/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:27:54 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 12:30:35 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;
	size_t	i;

	i = ft_strlen(s1);
	if (n > i)
		ptr = (char *)malloc((i + 1) * sizeof(char));
	else
		ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*(s1 + i) && n--)
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
