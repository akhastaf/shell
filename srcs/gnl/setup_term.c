/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:18:27 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 16:20:09 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
