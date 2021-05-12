/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refactor_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:18:21 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/11 17:15:15 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char    *ft_tilde(char *s, char *line, int i)
{
    char *tmp;
    char *tmp1;

    if (s[i + 1] == '+' && ft_getenv("PWD") && (ft_is_space(s[i+ 2]) || s[i+2]==0))
    {
        tmp = ft_getenv("PWD");
        tmp1 = ft_strjoin(line, tmp);
        free(tmp);
        return tmp1;
    }
    else if (s[i + 1] == '-' && ft_getpath("OLDPWD")  && (ft_is_space(s[i+ 2]) || s[i+2]==0))
    {
        tmp = ft_getenv("OLDPWD");
        tmp1 = ft_strjoin(line, tmp);
        free(tmp);
        return tmp1;
    }
    // else if (s[i + 1] == '+' || s[i + 1] == '-')
    // {
    //         line = ft_strappend(line, '~');
    //         line = ft_strappend(line, s[i+1]);
    // }
    else
    {
        if (ft_getenv("HOME"))
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
    char *var;
    char *str;
    char *line;
    int i;
    int j;

    line = NULL;
    i = 0;
    while (s[i])
    {
        if (s[i + 1] && s[i] == '\'' && s[(i - 1 < 0 ? 1 : i - 1)] != '\\')
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
                printf("%d\n", g_sh.status);
                line = ft_strjoin(line, ft_itoa(g_sh.status));
                i++;
            }
            else if (var[0])
            {
                str = ft_getenv(var);
                line = ft_strjoin(line, str);
                free(str);
                i = i + ft_strlen(var);
                free(var);
            }
            else
                line = ft_strappend(line, s[i]);
        }
        else if (s[i] == '~'  && s[(i - 1 < 0 ? 1 : i - 1)] != '\\')
        {
            line = ft_tilde(s, line, i);
            // i = (s[i + 1] == '+' ? i + 1 : i) + (s[i + 1] == '-' ? i + 1 : i);
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
