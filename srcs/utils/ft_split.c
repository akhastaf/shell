/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:36:14 by akhastaf          #+#    #+#             */
/*   Updated: 2021/04/29 16:54:55 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     is_seperator(char *s, int i, char *set)
{
    int j;
    
    j = 0;
    while (set[j])
    {
        if (set[j] == s[i] && (s[ternary(i - 1 < 0, 1, i - 1)] != '\\' || !is_specialcar(s[i])))
			return 1;
        j++;
    }
    return 0;
}

static		int		ft_wordscount(const char *str, char *set)
{
	int		i;
	int		wc;
	char	*s;
	int		len;

	s = (char*)str;
	i = 0;
	wc = 0;
	len = ft_strlen(s);
	if (!is_seperator(s, i, set))
		wc++;
	while (i < len)
	{
		if ((s[i] == 34 || s[i] == 39) && (s[ternary(i - 1 < 0,  0, i - 1)] != '\\'))
        {
            i++;
            while (s[i] != 34 && s[i] != 39 && s[ternary(i - 1 < 0,  0, i - 1)] != '\\' && s[i] != 0)
                i++;
        }
		if (s[ternary(i - 1 < 0,  0, i - 1)] != '\\' && is_seperator(s, i, set) && !is_seperator(s, i + 1, set) && s[i + 1])
			wc++;
		i++;
	}
	return (wc);
}

static	size_t		ft_wordlen(char *s, char *set, int i)
{
	int j;
	int len;

	j = 0;
	len = ft_strlen(s); 
	while (i < len && (!is_seperator(s, i, set) || (is_seperator(s, i, set) && s[ternary(i - 1 < 0, 0, i - 1)] == '\\')) && s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && (s[ternary(i - 1 < 0,  0, i - 1)] != '\\'))
        {
            i++;
			j++;
            while (s[i] != 34 && s[i] != 39 && s[ternary(i - 1 < 0,  0, i - 1)] != '\\' && s[i] != 0)
			{
                i++;
				j++;
			}
        }
		j++;
		i++;
	}
	// if (i < len && is_specialcar(s[i]))
	// 	j++;
	return (j);
}

static	void		*ft_dealocate(char ***t, int i)
{
	while (i >= 0)
	{
		free((*t)[i]);
		i--;
	}
	free(**t);
	return (NULL);
}

char				**ft_split(char const *s, char *set)
{
	char	**words;
	int		i;
	int		j;
	int		wc;
	size_t	len;

	i = 0;
	j = 0;
	wc = 0;
	if (!((char*)s))
		return (NULL);
	wc = ft_wordscount((char*)s, set);
	if (!(words = malloc((wc + 1) * sizeof(char*))))
		return (NULL);
	while (j < wc && ((char*)s)[i])
	{
		while (is_seperator(((char*)s), i, set) && ((char*)s)[i])
			i++;
		len = ft_wordlen((char*)s, set, i);
		if (!(words[j] = ft_substr((char*)s, i, len)))
			return (ft_dealocate(&words, j));
		j++;
		i = i + len;
	}
	words[j] = NULL;
	return (words);
}

// static		int		ft_wordscount(const char *str, char c)
// {
// 	int		i;
// 	int		wc;
// 	char	*s;

// 	s = (char*)str;
// 	i = 0;
// 	wc = 0;
// 	if (s[i] != c)
// 		wc++;
// 	while (s[i])
// 	{
// 		if (s[i] == c && s[ternary(i - 1 > 0, i - 1, 0)] != '\\' && s[i + 1] != c && s[i + 1])
// 			wc++;
// 		i++;
// 	}
// 	return (wc);
// }

// static	size_t		ft_wordlen(char *s, char c, int i)
// {
// 	int j;

// 	j = 0;
// 	while (s[i] != c && s[i] && !(s[i] = c && s[ternary(i - 1 > 0, i - 1, 0)] != '\\'))
// 	{
// 		j++;
// 		i++;
// 	}
// 	return (j);
// }

// static	void		*ft_dealocate(char ***t, int i)
// {
// 	while (i >= 0)
// 	{
// 		free((*t)[i]);
// 		i--;
// 	}
// 	free(**t);
// 	return (NULL);
// }

// char				**ft_split(char const *s, char c)
// {
// 	char	**words;
// 	int		i;
// 	int		j;
// 	int		wc;
// 	size_t	len;

// 	i = 0;
// 	j = 0;
// 	if (!((char*)s))
// 		return (NULL);
// 	wc = ft_wordscount((char*)s, c);
// 	if (!(words = malloc((wc + 1) * sizeof(char*))))
// 		return (NULL);
// 	while (j < wc && ((char*)s)[i])
// 	{
// 		while (((char*)s)[i] == c && ((char*)s)[i])
// 			i++;
// 		len = ft_wordlen((char*)s, c, i);
// 		if (!(words[j] = ft_substr((char*)s, i, len)))
// 			return (ft_dealocate(&words, j));
// 		j++;
// 		i = i + len;
// 	}
// 	words[j] = NULL;
// 	return (words);
// }