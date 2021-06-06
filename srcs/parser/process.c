/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:21:19 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 15:58:09 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*init_cmd(char *c)
{
	t_cmd	*cmd;
	char	**arg;

	c = ft_refactor_line(c);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->red = get_redirection(c);
	c = remove_red(c);
	arg = ft_split(c, " ");
	if (!arg || !arg[0])
		arg = ft_split("\t\t", " ");
	cmd->path = ft_getpath(ft_strdup(arg[0]), 0);
	ft_argmap(&arg, ft_putbackslash);
	cmd->arg = arg;
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	ft_free(&c);
	return (cmd);
}

void	process_pipeline(t_pipeline *p)
{
	char	**cmds;
	t_cmd	*cmd;
	int		i;

	cmds = ft_split(p->str, "|");
	i = 0;
	p->cmd = NULL;
	while (cmds[i] && !ft_is_empty(cmds[i]))
	{
		cmd = init_cmd(cmds[i]);
		ft_lstadd_back(&(p->cmd), ft_lstnew(cmd));
		i++;
	}
	ft_delete_arg(cmds);
}

void	delete_red(void *red)
{
	free(((t_red *)red)->file);
	free(((t_red *)red)->type);
	free(red);
}

void	delete_cmd(void *cmd)
{
	if (!(t_cmd *)cmd)
		return ;
	free(((t_cmd *)cmd)->path);
	if (((t_cmd *)cmd)->arg)
		ft_delete_arg(((t_cmd *)cmd)->arg);
	ft_lstclear(&(((t_cmd *)cmd)->red), delete_red);
	free(cmd);
}

void	delete_pipe(void *p)
{
	free(((t_pipeline *)p)->str);
	ft_lstclear(&(((t_pipeline *)p)->cmd), delete_cmd);
	free(p);
}
