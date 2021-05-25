/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:21:19 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/21 18:06:51 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    init_pipeline(void)
{
    char **pipeline;
    t_pipeline *p;
    int i;
    
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
        free(pipeline);
    }
}

void    process_pipeline(t_pipeline *p)
{
    char **arg;
    char **cmds;
    t_cmd *cmd;
    int     i;
    
    cmds = ft_split(p->str, "|");
    i = 0;
    p->cmd = NULL;
    while (cmds[i] && !ft_is_empty(cmds[i]))
    {
        cmds[i] = ft_refactor_line(cmds[i]);
        cmd = malloc(sizeof(t_cmd));
        cmd->red = get_redirection(cmds[i]);
        cmds[i] = remove_red(cmds[i]);
        arg = ft_split(cmds[i], " ");
        if (arg && arg[0])
        {
            cmd->path = ft_getpath(ft_strdup(arg[0]));
            ft_argmap(&arg, ft_putbackslash);
        }
        cmd->arg = arg;
        cmd->fdin = 0;
        cmd->fdout = 0;
        cmd->pipe[0] = -1;
        cmd->pipe[1] = -1;
        if (!(cmd->path))
            cmd->path = ft_strdup("");
        ft_lstadd_back(&(p->cmd), ft_lstnew(cmd));
        i++;
    }
    ft_delete_arg(cmds);
}
void    delete_red(void *red)
{
    free(((t_red*)red)->file);
    free(((t_red*)red)->type); 
    free(red);
}
void    delete_cmd(void *cmd)
{
    free(((t_cmd*)cmd)->path);
    ft_delete_arg(((t_cmd*)cmd)->arg);
    ft_lstclear(&(((t_cmd*)cmd)->red), delete_red);
    free(cmd);
}
void    delete_pipe(void *p)
{
    free(((t_pipeline*)p)->str);
    ft_lstclear(&(((t_pipeline*)p)->cmd), delete_cmd);
    free(p);
}