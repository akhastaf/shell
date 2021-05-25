/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:40:43 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 11:41:12 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_puterror(char *f, char *ar, char *l)
{
	if (f)
		ft_putstr_fd(f, 2);
	if (ar)
		ft_putstr_fd(ar, 2);
	if (l)
		ft_putendl_fd(l, 2);
}
