/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:04:02 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/13 15:26:39 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	find_red(char *cmd, int *i)
{
	char	*tmp;

	if (cmd[*i] == '>' && cmd[(*i) + 1] == '>'
		&& cmd[ternary(i - 1 < 0, 0, (*i) - 1)] != '\\')
	{
		(*i) += 2;
		tmp = ft_getword(cmd + (*i) + 1, " ><|;");
		(*i) += ft_strlen(tmp);
		free(tmp);
	}
	else if ((cmd[*i] == '<' || cmd[*i] == '>')
		&& cmd[ternary(*i - 1 < 0, 0, (*i) - 1)] != '\\')
	{
		(*i)++;
		tmp = ft_getword(cmd + (*i) + 1, " ><|;");
		(*i) += ft_strlen(tmp);
		free(tmp);
	}
	else
		return (cmd[*i]);
	return (0);
}

char	*remove_red(char *cmd)
{
	int		i;
	int		j;
	char	*new;
	int		sq;
	int		q;

	new = malloc(ft_strlen(cmd) + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	sq = 0;
	q = 0;
	while (cmd[++i])
	{
		ft_quotes(cmd, i, &q, &sq);
		if (find_red(cmd, &i))
		{
			new[j] = cmd[i];
			j++;
		}
	}
	new[j] = 0;
	ft_free(&cmd);
	return (new);
}
