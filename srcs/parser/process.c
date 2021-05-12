/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:21:19 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/12 14:06:25 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    init_pipeline(void)
{
    char **pipeline;
    t_pipeline *p;
    int i;
    
    p = NULL;
    if (g_sh.line)
    {
        pipeline = ft_split(g_sh.line, ";");
        i = 0;
        while (pipeline[i])
        {
            p = malloc(sizeof(t_pipeline));
            p->str = pipeline[i];
            p->cmd = NULL;
            ft_lstadd_back(&g_sh.pipeline, ft_lstnew(p));
            i++;
        }
    }
}

void    process_pipeline(t_pipeline *p)
{
    char **arg;
    char **cmds;
    t_cmd *cmd;
    int     i;
    
    p->str = ft_refactor_line(p->str);
    cmds = ft_split(p->str, "|");
    i = 0;
    p->cmd = NULL;
    while (cmds[i])
    {
        cmd = malloc(sizeof(t_cmd));
        cmd->red = get_redirection(cmds[i]);
        cmds[i] = remove_red(cmds[i]);
        arg = ft_split(cmds[i], " ");
        cmd->path = ft_getpath(ft_strremove(ft_strremove(ft_strremove(ft_putbackslash(ft_strdup(arg[0])), '\''), '"'), '\\'));
        ft_argmap(&arg, ft_putbackslash);
        cmd->arg = arg;
        cmd->fdin = 0;
        cmd->fdout = 0;
        cmd->pipe[0] = -1;
        cmd->pipe[1] = -1;
        ft_lstadd_back(&(p->cmd), ft_lstnew(cmd));
        i++;
    }
}
void    delete_red(void *red)
{
    free(((t_red*)red)->file);
    free(((t_red*)red)->type); 
}
void    delete_cmd(void *cmd)
{
    free(((t_cmd*)cmd)->path);
    ft_delete_arg(((t_cmd*)cmd)->arg);
    ft_lstclear(&(((t_cmd*)cmd)->red), delete_red);
}
void    delete_pipe(void *p)
{
    free(((t_pipeline*)p)->str);
    ft_lstclear(&(((t_pipeline*)p)->cmd), delete_cmd);
}