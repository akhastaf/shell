/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:34:35 by akhastaf          #+#    #+#             */
/*   Updated: 2021/04/29 16:41:32 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_getpath(char *file)
{
    struct stat sb;
    char **path;
    char *tmp;
    char *filepath;
    char *pathenv;
    int i;

    i = 0;
    pathenv = ft_getenv("PATH");
    if (ft_is_empty(file) || file[0] == '.' || ft_isbuiltins(file) || !pathenv || ft_strchr(file, '/'))
    {
        free(pathenv);
        return (file);
    }
    path = ft_split(pathenv, ":");
    free(pathenv);
    while (path[i])
    {
        filepath = ft_strjoin(path[i], "/");
        tmp = filepath;
        filepath = ft_strjoin(filepath, file);
        free(tmp);
        if (!stat(filepath, &sb))
        {
            free(file);
            ft_delete_arg(path);
            return filepath; 
        }
        free(filepath);
        i++;
    }
    ft_delete_arg(path);
    return (file);
}