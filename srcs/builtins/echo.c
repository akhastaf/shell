/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:47:12 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 15:29:24 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_dashn(char **arg, int *index)
{
	int	n;
	int	l;

	n = 0;
	*index = 1;
	while (arg[*index])
	{
		if (!ft_strcmp(arg[*index], "-n"))
			n = 1;
		else if (!ft_strncmp(arg[*index], "-n", 2))
		{
			l = 1;
			while (arg[*index][l] == 'n')
				l++;
			if (!arg[*index][l])
				n = 1;
			else
				break ;
		}
		else
			break ;
		(*index)++;
	}
	*index -= 1;
	return (n);
}

int	builtins_echo(char **arg)
{
	int		n;
	int		i;

	n = check_dashn(arg, &i);
	while (arg[++i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
