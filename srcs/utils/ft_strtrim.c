/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:11:54 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 20:13:04 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_strstart(char *s, char *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == set[j] && set[j])
		{
			j = 0;
			i++;
		}
		else if (!set[j])
			break ;
		else
			j++;
	}
	return (i);
}

static size_t	ft_strend(char *s, char *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s) - 1;
	j = 0;
	while (i)
	{
		if (s[i] == set[j] && s[ternary(i - 1 > 0, i - 1, 1)] != '\\' && set[j])
		{
			j = 0;
			i--;
		}
		else if (!set[j])
			break ;
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	char	*c;
	char	*str;
	size_t	start;
	size_t	end;

	s = (char *)s1;
	c = (char *)set;
	if (!s1 || !set)
		return (NULL);
	start = ft_strstart(s, c);
	end = ft_strend(s, c);
	if (start == ft_strlen(s1))
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = ft_substr(s, start, (end - start + 1));
	return (str);
}
