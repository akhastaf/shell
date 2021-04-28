/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:32:36 by akhastaf          #+#    #+#             */
/*   Updated: 2021/04/19 17:19:40 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
        if (cmd[i] == '>' && cmd[i + 1] == '>')
        {
            type = ft_strdup(">>");
            i++;
        }
        else if (cmd[i] == '>')
            type = ft_strdup(">");
        else if (cmd[i] == '<')
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
        if (cmd[i] == '>' && cmd[i + 1] == '>')
        {
            i += 2;
            tmp = ft_getword(cmd + i + 1, " ><|;");
            i += ft_strlen(tmp);
            free(tmp);
        }
        else if (cmd[i] == '<' || cmd[i] == '>')
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