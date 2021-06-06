/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:12:04 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 20:12:05 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_argcmp(char **arg, char *s)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strnstr(arg[i], s, ft_strlen(arg[i])))
			return (0);
		i++;
	}
	return (1);
}
