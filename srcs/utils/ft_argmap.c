/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:30:34 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/21 15:40:57 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_argmap(char ***arg, char *(*map)(char *))
{
    char *tmp;
    int i;

    i = 0;
    while ((*arg)[i])
    {
        
        (*arg)[i] = map((*arg)[i]);
        tmp = (*arg)[i];
        (*arg)[i] = ft_strtrim((*arg)[i], " \t");
        free(tmp);
        (*arg)[i] = ft_strremove((*arg)[i], '\'');
        (*arg)[i] = ft_strremove((*arg)[i], '"');
        (*arg)[i] = ft_strremove((*arg)[i], '\\');
        i++;
    }
}