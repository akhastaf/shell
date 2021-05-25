/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:08:17 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 16:21:36 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_hist(char *s)
{
	t_list	*new;

	if (!s || !*s)
		return ;
	ft_lstadd_front(&(g_sh.hist), ft_lstnew(strdup(s)));
}

void	up_hist(void)
{
	int		len;
	char	*tmp;

	if (!g_sh.hist)
		return ;
	if (g_sh.line && !g_sh.tmp_hist)
		g_sh.tmp_line = ft_strdup(g_sh.line);
	if (!g_sh.tmp_hist)
		g_sh.tmp_hist = g_sh.hist;
	else if (g_sh.tmp_hist->next)
		g_sh.tmp_hist = g_sh.tmp_hist->next;
	len = 0;
	if (g_sh.line)
		len = ft_strlen(g_sh.line);
	while (--len >= 0)
		backspace();
	tmp = g_sh.line;
	g_sh.line = ft_strdup(g_sh.tmp_hist->data);
	free(tmp);
	tputs(g_sh.line, 1, putchar_tc);
}

void	line_form_hist(void)
{
	char	*tmp;

	g_sh.tmp_hist = g_sh.tmp_hist->prev;
	tmp = g_sh.line;
	g_sh.line = ft_strdup(g_sh.tmp_hist->data);
	free(tmp);
	tputs(g_sh.line, 1, putchar_tc);
}

void	backedup_line(void)
{
	char	*tmp;

	tmp = g_sh.line;
	g_sh.line = ft_strdup(g_sh.tmp_line);
	ft_free(&g_sh.tmp_line);
	free(tmp);
	g_sh.tmp_hist = NULL;
	tputs(g_sh.line, 1, putchar_tc);
}

void	down_hist(void)
{
	int		len;

	if (!g_sh.tmp_hist)
		return ;
	len = 0;
	if (g_sh.line)
		len = ft_strlen(g_sh.line);
	while (--len >= 0)
		backspace();
	if (g_sh.tmp_hist->prev)
		line_form_hist();
	else if (g_sh.tmp_line)
		backedup_line();
	else
	{
		g_sh.tmp_hist = NULL;
		ft_free(&g_sh.line);
	}
}
