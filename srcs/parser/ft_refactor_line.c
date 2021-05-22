/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refactor_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:18:21 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/21 15:27:41 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char    *ft_tilde(char *s, char *line, int i)
{
    char *tmp;
    char *tmp1;

    if (s[i + 1] == '+' && ft_checkenv("PWD") && (ft_is_space(s[i+ 2]) || s[i+2]==0))
    {
        tmp = ft_getenv("PWD");
        tmp1 = ft_strjoin(line, tmp);
        free(tmp);
        return tmp1;
    }
    else if (s[i + 1] == '-' && ft_checkenv("OLDPWD")  && (ft_is_space(s[i+ 2]) || s[i+2]==0))
    {
        tmp = ft_getenv("OLDPWD");
        tmp1 = ft_strjoin(line, tmp);
        free(tmp);
        return tmp1;
    }
    else if (s[i + 1] == '+' || s[i + 1] == '-')
    {
            line = ft_strappend(line, '~');
            line = ft_strappend(line, s[i+1]);
    }
    else
    {
        if (ft_checkenv("HOME"))
        {
            tmp = ft_getenv("HOME");
            tmp1 = ft_strjoin(line, tmp);
            free(tmp);
            return tmp1;
        }
        else
            return ft_strjoin(line, g_sh.home);
    }
    return line;
}

char    *ft_refactor_line(char *s)
{
    char *tmp;
    char *var;
    char *str;
    char *line;
    int i;
    int j;
    int q;
    int sq;

    line = NULL;
    i = 0;
    sq = 0;
    q = 0;
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
        if (s[i + 1] && s[i] == '\'' && s[(i - 1 < 0 ? 1 : i - 1)] != '\\' && !q)
        {
            line = ft_strappend(line, s[i]);
            i++;
            while (s[i] && s[i] != '\'')
            {
                line = ft_strappend(line, s[i]);
                i++;
            }
        }
        if (s[i] == '$' && !ft_is_space(s[i + 1]) && s[(i - 1 < 0 ? 1 : i - 1)] != '\\')
        {
            var = ft_getword(s + i + 1, "\" |'\\$=,][@");
            if (s[i + 1] == '?')
            {
                tmp = line;
                line = ft_strjoin(line, ft_itoa(g_sh.status));
                free(tmp);
                i++;
            }
            else if (var[0])
            {
                str = ft_getenv(var);
                str = ft_keepq(str);
                tmp = line;
                line = ft_strjoin(line, str);
                free(str);
                free(tmp);
                i = i + ft_strlen(var);
                free(var);
            }
            else
                line = ft_strappend(line, s[i]);
        }
        else if (s[i] == '~'  && s[(i - 1 < 0 ? 1 : i - 1)] != '\\')
        {
            line = ft_tilde(s, line, i);
            if (s[i + 1] == '+' || s[i + 1] == '-')
                i = i + 1;
        }
        else
            line = ft_strappend(line, s[i]);
        i++;
    }
    free(s);
    if (!line)
        return ft_strdup("");
    return line;
}
