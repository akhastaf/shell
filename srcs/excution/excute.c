/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:24:47 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/21 17:42:52 by akhastaf         ###   ########.fr       */
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
    f = get_value(g_sh.builtins, path);
    g_sh.status = f(arg);
}

void    check_errors(t_cmd *cmd, int err)
{
    struct stat sb;
    char *path;
    char *spath;
    DIR *dir;
    

    path = ft_getenv("PATH");
    if (!ft_strchr(cmd->path, '/') && (!path || ft_is_empty(path)))
        spath = ft_strjoin("./", cmd->path);
    dir = opendir(spath);
    if ((dir && (ft_strchr(cmd->path, '/') || !path || ft_is_empty(path))) || (errno == 13 && (ft_strchr(cmd->path, '/') || !path || ft_is_empty(path))))
    {
        printf("minishell: %s: is a directory\n", cmd->path);
        closedir(dir);
        exit(126);
    }
    else if ((!path || ft_is_empty(path)) && stat(spath, &sb))
    {
        printf("minishell: %s: No such file or directory\n", cmd->path);
        exit(127);
    }
    else if (err == 2 || dir)
    {
        printf("minishell: %s: command not found\n", cmd->path);
        exit(127);
    }
    else if (err != 8)
    {
        printf("minishell: %s: Permission denied\n", cmd->path);
        exit(126);
    }
}

void    magic_box(t_pipeline *p)
{
    t_list *tmp;
    fun_ptr *f;

    tmp = p->cmd;
    if (!tmp->next && !ft_is_empty(((t_cmd*)tmp->data)->path) && ft_isbuiltins(((t_cmd*)tmp->data)->path))
    {
        setup_redirection(tmp->data);
        if (!g_sh.error )
            execute_builtins(((t_cmd*)tmp->data)->path, ((t_cmd*)tmp->data)->arg);
        tmp = tmp->next;
    }
    while (tmp && !ft_is_empty(((t_cmd*)tmp->data)->path))
    {
        g_sh.is_pipe = 1;
        g_sh.pid = fork();
        if (!g_sh.pid)
        {
            setup_pipe(tmp);
            setup_redirection(tmp->data);
            if (!g_sh.error && ft_isbuiltins(((t_cmd*)tmp->data)->path))
            {
                execute_builtins(((t_cmd*)tmp->data)->path, ((t_cmd*)tmp->data)->arg);
                exit(g_sh.status);
            }
            else if (!g_sh.error)
            {
                if (execve(((t_cmd*)tmp->data)->path, ((t_cmd*)tmp->data)->arg, ht_totable(g_sh.env)))
                    check_errors(tmp->data, errno);
            }
            else
                exit(1);
        }
        close(((t_cmd*)tmp->data)->pipe[1]);
        if (tmp->prev)
            close(((t_cmd*)tmp->prev->data)->pipe[0]);
        tmp = tmp->next;
    }
    g_sh.is_pipe = 0;
    close_pipe(p);
    // reset_std();
    waitpid(g_sh.pid, &g_sh.status, 0);
    if (WIFSIGNALED(g_sh.status))
        g_sh.status = 128 + WTERMSIG(g_sh.status);
    else
        g_sh.status = WEXITSTATUS(g_sh.status);
    while(wait(NULL)>0);
}

void     excute()
{
    t_list *tmp;

    tmp = g_sh.pipeline;
    while (tmp)
    {
        warp_excute(((t_pipeline*)tmp->data));
        open_pipes(((t_pipeline*)tmp->data));
        if (((t_pipeline*)tmp->data)->cmd)
            magic_box(tmp->data);
        // print_cmd(tmp->data);
        reset_std();
        if (!tmp->next)
            ft_set_lstcmd(((t_pipeline*)tmp->data)->cmd);
        tmp = tmp->next;
    }
}
int     warp_excute(t_pipeline *p)
{
    process_pipeline(p);
    return 0;
}
