/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:05:28 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 16:44:57 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init(char **type, t_list **redlist, int *i)
{
	*type = NULL;
	*i = 0;
	*redlist = NULL;
}

static t_red	*init_red(char *file, char *type)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	red->file = file;
	red->type = type;
	return (red);
}

static char	*get_file(char *cmd, char *type, int *i)
{
	char	*tmp;
	char	*file;

	file = NULL;
	if (type)
	{
		tmp = ft_getword(cmd + (*i) + 1, " ><|;");
		file = ft_strtrim(tmp, " ");
		free(tmp);
		file = ft_strremove(file, '\'');
		file = ft_strremove(file, '"');
		file = ft_refactor_line(file);
	}
	return (file);
}

static char	*get_type(char *cmd, int *i)
{
	char	*type;

	type = NULL;
	if (cmd[*i] == '>' && cmd[(*i) + 1] == '>'
		&& cmd[ternary((*i) - 1 < 0, 0, (*i) - 1)] != '\\')
	{
		type = ft_strdup(">>");
		(*i)++;
	}
	else if (cmd[*i] == '>' && cmd[ternary((*i) - 1 < 0, 0, (*i) - 1)] != '\\')
		type = ft_strdup(">");
	else if (cmd[*i] == '<' && cmd[ternary((*i) - 1 < 0, 0, (*i) - 1)] != '\\')
		type = ft_strdup("<");
	return (type);
}

t_list	*get_redirection(char *cmd)
{
	int		i;
	char	*type;
	t_red	*red;
	t_list	*redlist;
	char	*file;

	init(&type, &redlist, &i);
	while (++i < ft_strlen(cmd))
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] && cmd[i] != '"')
				i++;
		}
		type = get_type(cmd, &i);
		file = get_file(cmd, type, &i);
		if (type)
		{
			red = init_red(file, type);
			ft_lstadd_back(&redlist, ft_lstnew(red));
		}
		type = NULL;
	}
	return (redlist);
}
