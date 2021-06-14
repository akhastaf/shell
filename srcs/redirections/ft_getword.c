/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:07:02 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/13 15:26:33 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getword(char *word, char *set)
{
	int		i;
	int		q;
	int		sq;
	char	*w;

	i = 0;
	q = 0;
	sq = 0;
	ft_skip_space(word, &i);
	while (word[i])
	{
		ft_quotes(word, i, &q, &sq);
		if (ft_strchr(set, word[i]) && word[i] != ' ')
			break ;
		else if (word[i] == ' ' && !q && !sq)
			break ;
		i++;
	}
	w = ft_strndup(word, i);
	return (w);
}
