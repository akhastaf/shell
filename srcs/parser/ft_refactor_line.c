/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refactor_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:18:21 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/29 15:34:09 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	find_status(char **line, char *s, int *i)
{
	char	*tmp;

	if (s[*i + 1] == '?')
	{
		tmp = *line;
		*line = ft_strjoin(*line, ft_itoa(g_sh.status));
		free(tmp);
		(*i)++;
	}
}

static void	find_dollar(char **line, char *s, int *i)
{
	char	*tmp;
	char	*var;
	char	*str;

	if (s[*i] == '$' && !ft_is_space(s[*i + 1])
		&& s[ternary(*i - 1 < 0, 1, *i - 1)] != '\\')
	{
		var = ft_getword(s + *i + 1, "\" |'\\$=,][@");
		if (s[*i + 1] == '?')
			find_status(line, s, i);
		else if (var[0])
		{
			str = ft_getenv(var);
			str = ft_keepq(str);
			tmp = *line;
			*line = ft_strjoin(*line, str);
			free(str);
			free(tmp);
			*i = *i + ft_strlen(var);
			free(var);
		}
		else
			*line = ft_strappend(*line, s[*i]);
	}
}

static void	find_tilde(char **line, char *s, int *i)
{
	if (s[*i] == '~' && s[ternary(*i - 1 < 0, 1, *i - 1)] != '\\')
	{
		*line = ft_tilde(s, *line, *i);
		if (s[*i + 1] == '+' || s[*i + 1] == '-')
			*i = *i + 1;
	}
}

static void	check_before_d(char **line, char *s, int *i, int q)
{
	if (s[*i + 1] && s[*i] == '\''
		&& s[ternary(*i - 1 < 0, 1, *i - 1)] != '\\' && !q)
	{
		*line = ft_strappend(*line, s[*i]);
		(*i)++;
		while (s[*i] && s[*i] != '\'')
		{
			*line = ft_strappend(*line, s[*i]);
			(*i)++;
		}
	}
}

char	*ft_refactor_line(char *s)
{
	char	*line;
	int		i;
	int		j;
	int		q;
	int		sq;

	line = NULL;
	i = -1;
	sq = 0;
	q = 0;
	while (s[++i])
	{
		ft_quotes(s[i], &q, &sq);
		check_before_d(&line, s, &i, q);
		if (s[i] == '$')
			find_dollar(&line, s, &i);
		else if (s[i] == '~')
			find_tilde(&line, s, &i);
		else
			line = ft_strappend(line, s[i]);
	}
	if (!line)
		return (ft_strdup(""));
	return (line);
}
