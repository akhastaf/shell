/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:44:24 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 20:12:04 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_syntax(void)
{
	int	r;

	if (!g_sh.line || ft_is_empty(g_sh.line))
		return (NULL);
	r = check_pipe();
	if (r)
		return (g_sh.errors[r]);
	r = check_red();
	if (r)
		return (g_sh.errors[r]);
	r = check_quote();
	if (r)
		return (g_sh.errors[r]);
	return (NULL);
}

static int	check_pipetoken(void)
{
	if (ft_strnchr(g_sh.line, "||"))
		return (3);
	if (ft_strnchr(g_sh.line, ";;"))
		return (4);
	if (ft_strnchr(g_sh.line, "|;"))
		return (5);
	if (ft_strnchr(g_sh.line, ";|"))
		return (6);
	if (ft_strnchr(g_sh.line, ">|"))
		return (1);
	if (ft_strnchr(g_sh.line, "<|"))
		return (1);
	if (ft_strnchr(g_sh.line, "<;"))
		return (2);
	if (ft_strnchr(g_sh.line, ">;"))
		return (2);
	return (0);
}

int	check_pipe(void)
{
	int	l;

	l = 0;
	while (g_sh.line[l] == ' ')
		l++;
	if (g_sh.line[l] == '|')
		return (1);
	else if (g_sh.line[l] == ';')
		return (2);
	l = ft_strlen(g_sh.line);
	l--;
	while (g_sh.line[l])
	{
		if (g_sh.line[l] == ' ')
			l--;
		if (g_sh.line[l] == '|')
			return (1);
		else
			break ;
	}
	return (check_pipetoken());
	return (0);
}

int	check_red(void)
{
	int	i;

	check_forbiden();
	i = -1;
	while (g_sh.line[++i])
	{
		if (g_sh.line[i] == '>' && g_sh.line[i + 1] == '>')
		{
			i += 2;
			ft_skip_space(g_sh.line, &i);
			if (g_sh.line[i] != '$' && (is_specialcar(g_sh.line[i])
					|| !g_sh.line[i]))
				return (9);
		}
		else if (g_sh.line[i] == '<' && g_sh.line[i + 1] == '<')
		{
			i += 2;
			ft_skip_space(g_sh.line, &i);
			if (g_sh.line[i] != '$' && (is_specialcar(g_sh.line[i])
					|| !g_sh.line[i]))
				return (9);
		}
		else if (g_sh.line[i] == '>' || g_sh.line[i] == '<')
		{
			i++;
			ft_skip_space(g_sh.line, &i);
			if (g_sh.line[i] != '$' && (is_specialcar(g_sh.line[i]
						&& g_sh.line[i] != '\'' && g_sh.line[i] != '"')
					|| !g_sh.line[i]))
				return (9);
		}
	}
	return (0);
}

int	check_quote(void)
{
	if (count_doubleq(g_sh.line) % 2 != 0)
		return (10);
	if (count_singleq(g_sh.line) % 2 != 0)
		return (10);
	return (0);
}
