/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:06:58 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/10 13:41:55 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    minishell_loop(void)
{
    while (1)
    {
        ft_putstr_fd("\033[0;32mMinishell$> \033[0m", 1);
        tcgetattr(0, &g_sh.tc.init);
        gnl_term();
        tcsetattr(0, TCSANOW, &g_sh.tc.init);
        init_pipeline();
        //print_pipeline();
        g_sh.status = excute();
        ft_lstclear(&(g_sh.pipeline), delete_pipe);
        free(g_sh.line);
        g_sh.line = NULL;
    }
}

void    print_pipeline(void)
{
    t_list *tmp;
    int i;
    
    i = 0;
    tmp = g_sh.pipeline;
    while (tmp)
    {
        printf("%d\t\t|%s|\n", i, ((t_pipeline *)tmp->data)->str);
        tmp = tmp->next;
        i++;
    }
}