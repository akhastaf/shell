/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:35:55 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 16:19:11 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_printable(long c)
{
	char	bf[2];
	char	*tmp;

	bf[0] = c;
	bf[1] = '\0';
	if (g_sh.line)
	{
		tmp = g_sh.line;
		g_sh.line = ft_strjoin(g_sh.line, bf);
		free(tmp);
	}
	else
		g_sh.line = ft_strdup(bf);
	tputs(bf, 1, putchar_tc);
}

int	gnl_term(void)
{
	long	c;

	setup_term();
	signal(SIGINT, signals);
	signal(SIGQUIT, signals);
	c = 0;
	g_sh.tmp_hist = NULL;
	g_sh.tmp_line = NULL;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c >= 32 && c <= 126)
			get_printable(c);
		if (c == '\n')
			break ;
		handle_keys(c);
		c = 0;
	}
	if (g_sh.tmp_line)
		ft_free(&g_sh.tmp_line);
	if (!g_sh.line)
		g_sh.line = ft_strdup("");
	add_hist(g_sh.line);
	tputs("\n", 1, putchar_tc);
	return (1);
}

int	putchar_tc(int c)
{
	write(1, &c, 1);
	return (c);
}

void	backspace(void)
{
	char	*tmp;

	tmp = g_sh.line;
	tputs(tgetstr("le", NULL), 1, putchar_tc);
	tputs(tgetstr("dc", NULL), 1, putchar_tc);
	g_sh.line = ft_substr(g_sh.line, 0, ft_strlen(g_sh.line) - 1);
	free(tmp);
}

void	handle_keys(long c)
{
	if (c == 4 && (!g_sh.line || !*g_sh.line))
	{
		tcsetattr(0, TCSANOW, &g_sh.tc.init);
		printf("exit\n");
		exit(0);
	}
	if (c == DELETE && g_sh.line && *g_sh.line)
		backspace();
	if (c == UP)
		up_hist();
	if (c == DOWN)
		down_hist();
}
