/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbackslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:28:26 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/13 15:40:06 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init(int *i, int *q, int *sq)
{
	*i = -1;
	*q = 0;
	*sq = 0;
}

char	*ft_putbackslash(char *s, int j)
{
	int		i;
	int		q;
	int		sq;
	char	*new;

	init(&i, &q, &sq);
	new = NULL;
	while (s[++i])
	{
		ft_quotes(s, i, &q, &sq);
		if ((s[i] == '"' && sq) || (s[i] == '\\' && sq) || (s[i] == '\\'
				&& s[i + 1] != '\\' && s[i + 1] != '"' && s[i + 1] != '\''
				&& s[i + 1] != '$' && q)
			|| (s[i] == '\\' && s[i + 1] != '\\' && s[i + 1] != '"' && q))
		{
			new = ft_strappend(new, '\\');
			j++;
		}
		new = ft_strappend(new, s[i]);
	}
	if (s[0] != '\0')
		new[i + j] = 0;
	ft_free(&s);
	return (new);
}

char	*ft_keepq(char *s)
{
	char	*new;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == '"')
			new = ft_strappend(new, '\\');
		new = ft_strappend(new, s[i]);
		i++;
	}
	ft_free(&s);
	return (new);
}
