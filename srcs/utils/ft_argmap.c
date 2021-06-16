/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:30:34 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/16 14:59:24 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_argmap(char ***arg, char *(*map)(char *, int))
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*arg)[i])
	{
		(*arg)[i] = map((*arg)[i], 0);
		tmp = (*arg)[i];
		(*arg)[i] = ft_strtrim((*arg)[i], " \t");
		free(tmp);
		(*arg)[i] = ft_strremove((*arg)[i], '\'');
		(*arg)[i] = ft_strremove((*arg)[i], '"');
		(*arg)[i] = ft_strremove((*arg)[i], '\\');
		i++;
	}
}
