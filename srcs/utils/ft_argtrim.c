/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:12:13 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 20:12:14 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_argtrim(char **arg, char *set)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg[i])
	{
		tmp = arg[i];
		arg[i] = ft_strtrim(arg[i], set);
		free(tmp);
		i++;
	}
	return (arg);
}
