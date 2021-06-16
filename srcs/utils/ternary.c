/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:16:40 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/16 15:36:59 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ternary(int condition, int ret1, int ret2)
{
	if (condition && ret1 >= 0)
		return (ret1);
	else if (!condition && ret2 >= 0)
		return (ret2);
	return (0);
}
