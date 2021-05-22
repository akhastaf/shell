/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:32:36 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/21 17:26:07 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    setup_redirection(t_cmd *cmd)
{
    t_list *red;
    
    red = cmd->red;
    cmd->fdout = 0;
    cmd->fdin = 0;
    g_sh.error = 0;
    while (red)
    {
        if (red && ((t_red*)red->data)->type[0] == '<')
            cmd->fdin = open(((t_red*)red->data)->file, get_option(red->data), S_IRWXU);
        if (red && ((t_red*)red->data)->type[0] == '>')
            cmd->fdout = open(((t_red*)red->data)->file, get_option(red->data), S_IRWXU);
        if ((cmd->fdin < 0 || cmd->fdout < 0))
        {
            g_sh.error = 1;
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(((t_red*)red->data)->file, 2);
            ft_putstr_fd(": ", 2);
            ft_putendl_fd(strerror(errno), 2);
            g_sh.status = 1;
            return ;
        }
        if (red->next && cmd->fdout && ((t_red*)red->next->data)->type[0] != '<')
            close(cmd->fdout);
        if (red->next && cmd->fdin && ((t_red*)red->next->data)->type[0] == '<')
            close(cmd->fdin);
        red = red->next;
    }
    if (cmd->fdout)
        dup2(cmd->fdout, 1);
    if (cmd->fdin)
        dup2(cmd->fdin, 0);
}

static t_red    *init_red(char *file, char *type)
{
    t_red *red;

    red = malloc(sizeof(t_red));
    red->file = file;
    red->type = type;
    return (red);
}

char    *ft_getword(char *word, char *set)
{
    int i;
    int q;
    int sq;
    char *w;

    i = 0;
    q = 0;
    sq = 0;
    while (word[i] == ' ')
        i++;
    while(word[i])
    {
        if (word[i] == '\'' && !sq && !q)
            sq = 1;
        else if (word[i] == '\'' && sq)
            sq = 0;
        if (word[i] == '"' && !q && !sq)
            q = 1;
        else if (word[i] == '"' && q)
            q = 0;
        if (ft_strchr(set, word[i]) && word[i] != ' ')
            break;
        else if (word[i] == ' ' && !q && !sq)
            break;
        i++;
    }
    w = ft_strndup(word, i);
    return (w);
}

t_list   *get_redirection(char *cmd)
{
    int i;
    int j;
    int len;
    char *type;
    t_red *red;
    t_list *redlist;
    char *file;
    char *tmp;

    i = 0;
    j = 0;
    type = NULL;
    redlist = NULL;
    len = ft_strlen(cmd);
    while (i < len)
    {
        if (cmd[i] == '"')
        {
            i++;
            while (cmd[i] && cmd[i] != '"')
                i++;
        }
        if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[ternary(i - 1 < 0, 0, i - 1)] != '\\')
        {
            type = ft_strdup(">>");
            i++;
        }
        else if (cmd[i] == '>' && cmd[ternary(i - 1 < 0, 0, i - 1)] != '\\')
            type = ft_strdup(">");
        else if (cmd[i] == '<' && cmd[ternary(i - 1 < 0, 0, i - 1)] != '\\')
            type = ft_strdup("<");
        if (type)
        {
            tmp = ft_getword(cmd + i + 1, " ><|;");
            file = ft_strtrim(tmp, " ");
            free(tmp);
            file = ft_strremove(file, '\'');
            file = ft_strremove(file, '"');
            file = ft_refactor_line(file);
            red = init_red(file, type);
            ft_lstadd_back(&redlist, ft_lstnew(red));
        }
        type = NULL;
        i++;
    }
    return redlist;
}

int    get_option(t_red *red)
{
    int option;

    option = 0;
    if (red->type && red->type[0] == '>' && red->type[1] != '>')
        option = O_CREAT | O_WRONLY | O_TRUNC;
    else if (red->type && red->type[0] == '<')
        option = O_RDONLY;
    else if (red->type && !ft_strcmp(red->type, ">>"))
        option = O_CREAT | O_WRONLY | O_APPEND;
    return option;
}

char    *remove_red(char *cmd)
{
    int i;
    int j;
    int len;
    char *new;
    char *tmp;
    int sq;
    int q;

    new = malloc(ft_strlen(cmd) + 1);
    i = 0;
    j = 0;
    sq = 0;
    q = 0;
    tmp = NULL;
    while (cmd[i])
    {
        if (cmd[i] == '\'' && !sq && !q)
            sq = 1;
        else if (cmd[i] == '\'' && sq)
            sq = 0;
        if (cmd[i] == '"' && !q && !sq)
            q = 1;
        else if (cmd[i] == '"' && q)
            q = 0;
        if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[ternary(i - 1 < 0, 0, i - 1)] != '\\')
        {
            i += 2;
            tmp = ft_getword(cmd + i + 1, " ><|;");
            i += ft_strlen(tmp);
            free(tmp);
        }
        else if ((cmd[i] == '<' || cmd[i] == '>') && cmd[ternary(i - 1 < 0, 0, i - 1)] != '\\')
        {
            i++;
            tmp = ft_getword(cmd + i + 1, " ><|;");
            i += ft_strlen(tmp);
            free(tmp);
        }
        else
        {
            new[j] = cmd[i];
            j++;
        }
        i++;
    }
    new[j] = 0;
    if (cmd)
        free(cmd);
    return new;
}