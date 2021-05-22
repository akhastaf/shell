/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:44:24 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/21 17:54:46 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *check_syntax()
{
	int r;

	if (!g_sh.line || ft_is_empty(g_sh.line))
		return NULL;
	if ((r = check_pipe()))
		return g_sh.errors[r];
	if ((r = check_red()))
		return g_sh.errors[r];
	if ((r = check_quote()))
		return g_sh.errors[r];
	return NULL;
}

int     check_pipe()
{
	int l;

	l = 0;
	while (g_sh.line[l] == ' ')
		l++;
	if (g_sh.line[l] == '|')
		return 1;
	else if (g_sh.line[l] == ';')
		return 2;
	l = ft_strlen(g_sh.line);
	l--;
	while (g_sh.line[l])
	{
		if (g_sh.line[l] == ' ')
			l--;
		if (g_sh.line[l] == '|')
			return 1;
		else
			break ;
	}
	if (ft_strnchr(g_sh.line, "||"))
		return 3;
	if (ft_strnchr(g_sh.line, ";;"))
		return 4; 
	if (ft_strnchr(g_sh.line, "|;"))
		return 5;
	if (ft_strnchr(g_sh.line, ";|"))
		return 6;
	if (ft_strnchr(g_sh.line, ">|"))
		return 1;
	if (ft_strnchr(g_sh.line, "<|"))
		return 1;
	if (ft_strnchr(g_sh.line, "<;"))
		return 2;
	if (ft_strnchr(g_sh.line, ">;"))
		return 2;
	return 0;
}

int     check_red()
{
	int i;

	if (ft_strnchr(g_sh.line, "<<"))
		return 7;
	if (ft_strnchr(g_sh.line, ">>>"))
		return 8;
	i = 0;
	while (g_sh.line[i])
	{
		if (g_sh.line[i] == '>' && g_sh.line[i + 1] == '>')
		{
			i+= 2;
			while (g_sh.line[i] == ' ')
				i++;
			if (g_sh.line[i] != '$' && (is_specialcar(g_sh.line[i]) || !g_sh.line[i]))
				return 9;
		}
		else if (g_sh.line[i] == '>' || g_sh.line[i] == '<')
		{
			i++;
			while (g_sh.line[i] == ' ')
				i++;
			if (g_sh.line[i] != '$' && (is_specialcar(g_sh.line[i] && g_sh.line[i] != '\'' && g_sh.line[i] != '"') || !g_sh.line[i]))
				return 9;
		}
		i++;
	}
	return 0;
}

int     check_quote()
{
	if (count_doubleq(g_sh.line) % 2 != 0)
		return 10;
	if (count_singleq(g_sh.line) % 2 != 0)
		return 10;
	return 0;
}
