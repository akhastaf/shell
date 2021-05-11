/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:24:47 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/11 11:33:28 by akhastaf         ###   ########.fr       */
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
        tmp = tmp->next;
    }
}

void    execute_builtins(char *path, char **arg)
{
    fun_ptr *f;
    f = get_value(g_sh.builtins, path, ft_strlen(path));
    g_sh.status = f(arg);
}

void    magic_box(t_pipeline *p)
{
    t_list *tmp;
    fun_ptr *f;

    tmp = p->cmd;
    if (!tmp->next && ft_isbuiltins(((t_cmd*)tmp->data)->path))
    {
        execute_builtins(((t_cmd*)tmp->data)->path, ((t_cmd*)tmp->data)->arg);
        tmp = tmp->next;
    }
    while (tmp)
    {
        setup_redirection(((t_cmd*)tmp->data));
        g_sh.pid = fork();
        if (!g_sh.pid)
        {
            setup_pipe(tmp);
            if (ft_isbuiltins(((t_cmd*)tmp->data)->path))
            {
                f = get_value(g_sh.builtins, ((t_cmd*)tmp->data)->path, ft_strlen(((t_cmd*)tmp->data)->path));
                g_sh.status = f(((t_cmd*)tmp->data)->arg);
            }
            else
            {
                if (execve(((t_cmd*)tmp->data)->path, ((t_cmd*)tmp->data)->arg, ht_totable(g_sh.env)))
                    ft_putendl_fd(strerror(errno), 1);
            }
        }
        close(((t_cmd*)tmp->data)->pipe[1]);
        //reset_std();
        tmp = tmp->next;
    }
    close_pipe(p);
    waitpid(g_sh.pid, &g_sh.status, 0);
    while(wait(NULL)>0);
}

int     excute()
{
    t_list *tmp;

    tmp = g_sh.pipeline;
    while (tmp)
    {
        warp_excute(((t_pipeline*)tmp->data));
        open_pipes(((t_pipeline*)tmp->data));
        magic_box(tmp->data);
        reset_std();
        //close_pipe((t_pipeline*)(tmp->data));
        //waitpid(-1, &g_sh.status, 0);
        tmp = tmp->next;
    }
    
    return 0;
}
int     warp_excute(t_pipeline *p)
{
    process_pipeline(p);
    return 0;
    
}
