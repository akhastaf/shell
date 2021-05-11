/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ternary.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:16:40 by akhastaf          #+#    #+#             */
/*   Updated: 2021/04/29 16:22:51 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ternary(int condition, int ret1, int ret2)
{
	if (condition)
		return (ret1);
	else
		return (ret2);
}