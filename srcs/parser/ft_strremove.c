/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:38:00 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 16:38:21 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*init(char *s, int *q, int *sq, int *i)
{
	*sq = 0;
	*q = 0;
	*i = 0;
	return (malloc(sizeof(char) * (ft_strlen(s) + 1)));
}

static int	check_doubleq(char *s, int l, int sq, char c)
{
	if (c == '"' && s[l] == c && ((s[ternary(l - 1 > 0, l - 1, 0)] == '\\'
				&& count_backslash(ft_strndup(s, l)) % 2 != 0) || sq))
		return (1);
	return (0);
}

static int	check_backslash(char *s, int l, int sq, char c)
{
	if (c == '\\' && s[l] == c && (sq || (s[ternary(l - 1 > 0, l - 1, 0)] == '\\'
				&& count_backslash(ft_strndup(s, l)) % 2 != 0)))
		return (1);
	return (0);
}

static int	check_singleq(char *s, int l, char c)
{
	if ((s[l] != '\\' && c == '\\') || (s[l] != '"' && c == '"')
		|| (s[l] != '\'' && c == '\''))
		return (1);
	return (0);
}

char	*ft_strremove(char *s, char c)
{
	int		l;
	int		q;
	int		sq;
	int		i;
	char	*new;

	new = init(s, &q, &sq, &i);
	if (!new)
		return (NULL);
	l = -1;
	while (s[++l])
	{
		ft_quotes(s[l], &q, &sq);
		if (check_doubleq(s, l, sq, c))
			new[i++] = s[l];
		if ((c == '\'' && s[l] == c) && q)
			new[i++] = s[l];
		if (check_backslash(s, l, sq, c))
			new[i++] = s[l];
		if (check_singleq(s, l, c))
			new[i++] = s[l];
	}
	new[i] = 0;
	ft_free(&s);
	return (new);
}
