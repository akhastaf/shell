// #include "../../include/minishell.h"


// int     is_seperator(char c, char *set)
// {
//     int i;
    
//     i = 0;
//     while (set[i])
//     {
//         if (set[i] == c)
//             return 1;
//         i++;
//     }
//     return 0;
// }

// static		int		ft_wordscount(const char *str, char *set)
// {
// 	int		i;
// 	int		wc;
// 	char	*s;

// 	s = (char*)str;
// 	i = 0;
// 	wc = 0;
// 	if (!is_seperator(s[i], set))
// 		wc++;
// 	while (s[i])
// 	{
// 		if (s[i] == 34 || s[i] == 39)
//         {
//             i++;
//             while (s[i] != 34 && s[i] != 39)
//                 i++;
//         }
// 		if (is_seperator(s[i], set) && !is_seperator(s[i + 1], set) && s[i + 1])
// 			wc++;
// 		i++;
// 	}
// 	return (wc);
// }

// static	size_t		ft_wordlen(char *s, char *set, int i)
// {
// 	int j;

// 	j = 0;
// 	while (!is_seperator(s[i], set) && s[i])
// 	{
// 		if (s[i] == 34 || s[i] == 39)
//         {
//             i++;
// 			j++;
//             while (s[i] != 34 && s[i] != 39)
// 			{
//                 i++;
// 				j++;
// 			}
//         }
// 		j++;
// 		i++;
// 	}
// 	return (j);
// }

// static	void		*ft_dealocate(char ***tab, int i)
// {
// 	while (i >= 0)
// 	{
// 		free((*tab)[i]);
// 		i--;
// 	}
// 	free(**tab);
// 	return (NULL);
// }

// char				**ft_split_two(char const *s, char *set)
// {
// 	char	**words;
// 	int		i;
// 	int		j;
// 	int		wc;
// 	size_t	len;

// 	i = 0;
// 	j = 0;
// 	wc = 0;
// 	if (!((char*)s))
// 		return (NULL);
// 	wc = ft_wordscount((char*)s, set);
// 	if (!(words = malloc((wc + 1) * sizeof(char*))))
// 		return (NULL);
// 	while (j < wc && ((char*)s)[i])
// 	{
// 		while (is_seperator(((char*)s)[i], set) && ((char*)s)[i])
// 			i++;
// 		len = ft_wordlen((char*)s, set, i);
// 		if (!(words[j] = ft_substr((char*)s, i, len)))
// 			return (ft_dealocate(&words, j));
// 		j++;
// 		i = i + len;
// 	}
// 	words[j] = NULL;
// 	return (words);
// }