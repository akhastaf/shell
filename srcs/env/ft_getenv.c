/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:35:29 by akhastaf          #+#    #+#             */
/*   Updated: 2021/04/14 16:19:18 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *ft_getenv(char *var)
{
    char *v;
    
    v = get_value(g_sh.env, var, ft_strlen(var)); 
    if (v)
        return ft_strdup(v);
    return NULL;
}
