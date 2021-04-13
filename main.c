/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:17:01 by akhastaf          #+#    #+#             */
/*   Updated: 2021/04/13 14:37:44 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int     main(int ac, char **av, char **env)
{
    init_env(env);
    //init_builtins();
}


void    init_env(char **env)
{
    size_t l;
    int i;
    int n;
    char    *key;
    char    *val;

    l = ft_argsize(env);
    init_hashtable(&(g_sh.env), l);
    i = 0;
    while (i < l)
    {
        n =ft_strchrn(env[i], '=');
        key = ft_strndup(env[i], n);
        val = ft_strdup(env[i] + n + 1);
        insert_to_table(g_sh.env, key, val, ft_strlen(key));
        i++;
    }
}