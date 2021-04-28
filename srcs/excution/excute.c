/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:24:47 by akhastaf          #+#    #+#             */
/*   Updated: 2021/04/23 13:20:58 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    print_red(t_list *red)
{
    t_list *tmp;
    
    tmp = red;
	while (tmp)
	{
		printf("type : %s | file : %s\n", ((t_red*)tmp->data)->type, ((t_red*)tmp->data)->file);
		tmp = tmp->next;
	}
}

void    print_cmd(t_pipeline *p)
{
    t_list *tmp;
    
    tmp = p->cmd;
    while (tmp)
    {
        // if (is_builtins(tmp->path) && !tmp->next)
        //     // excute builtins
        // else
        printf("|path : %s|\n", ((t_cmd*)tmp->data)->path);
        ft_argprint(((t_cmd*)tmp->data)->arg);
        print_red(((t_cmd*)tmp->data)->red);
        if (tmp->next)
            ft_putendl_fd("opr : |", 1);
        tmp = tmp->next;
    }
}


int     excute()
{
    t_list *tmp;

    tmp = g_sh.pipeline;
    while (tmp)
    {
        warp_excute(((t_pipeline*)tmp->data));
        print_cmd(((t_pipeline*)tmp->data));
        if (tmp->next)
            ft_putendl_fd("opr : ;", 1);
        tmp = tmp->next;
    }
    
    return 0;
}
int     warp_excute(t_pipeline *p)
{
    process_pipeline(p);
    return 0;
    
}

char    *ft_putbackslash(char *s)
{
    int i;
    int j;
    int q;
    int sq;
    char *new;

    i = 0;
    q = 0;
    sq = 0;
    j = 0;
    if (!s[0])
        return (ft_strdup(s));
    new = NULL;
    while (s[i])
    {
        if (s[i] == '\'' && !sq && !q)
            sq = 1;
        else if (s[i] == '\'' && sq )
            sq = 0;
        if (s[i] == '"' && !q && !sq)
            q = 1;
        else if (s[i] == '"' && q)
            q = 0;
        if ((s[i] == '"' && sq) || (s[i] == '\\' && sq) || (s[i] == '\\' && s[i +1] != '\\' && s[i + 1] != '"' && s[i + 1] != '$' && q))
        {
            new = ft_strappend(new, '\\');
            j++;
        }
        new = ft_strappend(new, s[i]);
        i++;
    }
    if (s[0] != '\0')
        new[i + j] = 0;
    if (s)
        free(s);
    return new;
}

