/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:36:14 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/14 14:54:57 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_split(int *i, int *j, int *wc)
{
	*i = 0;
	*j = -1;
	*wc = 0;
}

static int	ft_wordscount(char *s, char *set)
{
	int		i;
	int		wc;
	int		len;

	i = -1;
	wc = 0;
	len = ft_strlen(s);
	if (!is_seperator(s, 0, set))
		wc++;
	while (++i < len)
	{
		if ((s[i] == 34 || s[i] == 39)
			&& (s[ternary(i - 1 < 0, 0, i - 1)] != '\\'))
		{
			i++;
			while (s[i] != 34 && s[i] != 39
				&& s[ternary(i - 1 < 0, 0, i - 1)] != '\\' && s[i] != 0)
				i++;
		}
		if (s[ternary(i - 1 < 0, 0, i - 1)] != '\\' && is_seperator(s, i, set)
			&& !is_seperator(s, i + 1, set) && s[i + 1])
			wc++;
	}
	return (wc);
}

static size_t	ft_wordlen(char *s, char *set, int i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(s);
	while (i < len && (!is_seperator(s, i, set) || (is_seperator(s, i, set)
				&& s[ternary(i - 1 < 0, 0, i - 1)] == '\\')) && s[i])
	{
		if (s[i] == '"' && s[ternary(i - 1 < 0, 0, i - 1)] != '\\')
		{
			increments(&i, &j);
			while (s[i] != '"' && !(s[i] == '"'
					&& s[ternary(i - 1 < 0, 0, i - 1)] == '\\') && s[i])
				increments(&i, &j);
		}
		else if (s[i] == '\'' && s[ternary(i - 1 < 0, 0, i - 1)] != '\\')
		{
			increments(&i, &j);
			while (s[i] != '\'' && !(s[i] == '\''
					&& s[ternary(i - 1 < 0, 0, i - 1)] == '\\') && s[i])
				increments(&i, &j);
		}
		increments(&i, &j);
	}
	return (j);
}

static void	skip_split(char *s, int *i, char *set, size_t *len)
{
	while (is_seperator(s, *i, set) && s[*i])
		(*i)++;
	*len = ft_wordlen(s, set, *i);
}

char	**ft_split(char const *s, char *set)
{
	char	**words;
	int		i;
	int		j;
	int		wc;
	size_t	len;

	init_split(&i, &j, &wc);
	if (!((char *)s))
		return (NULL);
	wc = ft_wordscount((char *)s, set);
	if (!wc)
		return (NULL);
	words = malloc((wc + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (++j < wc && ((char *)s)[i])
	{
		skip_split(((char *)s), &i, set, &len);
		words[j] = ft_substr((char *)s, i, len);
		if (!words[j])
			return (ft_dealocate(&words, j));
		i = i + len;
	}
	words[j] = NULL;
	return (words);
}
