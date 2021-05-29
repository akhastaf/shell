/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:38:00 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/28 11:34:26 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strremove(char *s, char c)
{
	int		l;
	int		q;
	int		sq;
	int		i;
	char	*new;

	q = 0;
	sq = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	l = -1;
	i = 0;
	while (s[++l])
	{
		ft_quotes(s[l], &q, &sq);
		if (c == '"' && s[l] == c && ((s[l - 1 > 0 ? l - 1 : 0] == '\\'
					&& count_backslash(ft_strndup(s, l)) % 2 != 0) || sq))
			new[i++] = s[l];
		if ((c == '\'' && s[l] == c) && q)
			new[i++] = s[l];
		if (c == '\\' && s[l] == c && (sq || (s[l - 1 > 0 ? l - 1 : 0] == '\\'
					&& count_backslash(ft_strndup(s, l)) % 2 != 0)))
			new[i++] = s[l];
		if ((s[l] != '\\' && c == '\\') || (s[l] != '"' && c == '"')
			|| (s[l] != '\'' && c == '\''))
			new[i++] = s[l];
	}
	new[i] = 0;
	if (s)
		free(s);
	return (new);
}
