/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:35:55 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/16 12:19:58 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}
void	signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_free(&g_sh.line);
		if (g_sh.tmp_line)
			ft_free(&g_sh.tmp_line);
		g_sh.tmp_hist = NULL;
		if (g_sh.pid == 0)
		{
			ft_putstr_fd("\n", 1);
			ft_putstr_fd("\033[0;32mMinishell$> \033[0m", 1);
		}
		else if (g_sh.pid)
			ft_putstr_fd("\n", 1);
		
	}
	if (sig == SIGQUIT)
	{
		if (g_sh.pid)
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	setup_term(void)
{
	g_sh.tc.name = getenv("TERM");
	if (!g_sh.tc.name)
		printf("TERM not set\n");
	tgetent(NULL, g_sh.tc.name);
	setupterm(NULL, STDOUT_FILENO, NULL);
	tcgetattr(0, &g_sh.tc.term);
	g_sh.tc.term.c_lflag = g_sh.tc.term.c_lflag & ~ICANON;
	g_sh.tc.term.c_lflag = g_sh.tc.term.c_lflag & ~ECHO;
	g_sh.tc.term.c_cc[VMIN] = 1;
	g_sh.tc.term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_sh.tc.term);
	g_sh.tc.cm = tgetstr("cm", NULL);
	g_sh.tc.ce = tgetstr("ce", NULL);
	g_sh.tc.dl = tgetstr("dl", NULL);
}

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
