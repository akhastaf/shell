/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:32:36 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/26 14:24:17 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	file_exist(t_cmd *cmd, char *file)
{
	if ((cmd->fdin < 0 || cmd->fdout < 0))
	{
		g_sh.error = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_sh.status = 1;
		return (0);
	}
	return (1);
}

static void	close_file(t_list *red, t_cmd *cmd)
{
	if (red->next && cmd->fdout
		&& ((t_red *)red->next->data)->type[0] != '<')
		close(cmd->fdout);
	if (red->next && cmd->fdin
		&& ((t_red *)red->next->data)->type[0] == '<')
		close(cmd->fdin);
}

void	setup_redirection(t_cmd *cmd)
{
	t_list	*red;

	red = cmd->red;
	cmd->fdout = 0;
	cmd->fdin = 0;
	while (red)
	{
		if (red && ((t_red *)red->data)->type[0] == '<')
			cmd->fdin = open(((t_red *)red->data)->file, get_option(red->data),
					S_IRWXU);
		if (red && ((t_red *)red->data)->type[0] == '>')
			cmd->fdout = open(((t_red *)red->data)->file, get_option(red->data),
					S_IRWXU);
		if (!file_exist(cmd, ((t_red *)red->data)->file))
			return ;
		close_file(red, cmd);
		red = red->next;
	}
	if (cmd->fdout)
		dup2(cmd->fdout, 1);
	if (cmd->fdin)
		dup2(cmd->fdin, 0);
}
