/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_lstcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:43:05 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/29 15:29:51 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*get_lstcmd(t_list *cmd)
{
	t_cmd	*lstcmd;

	lstcmd = NULL;
	if (cmd->next)
	{
		ht_delone(g_sh.env, "_", 1, free);
		return (NULL);
	}
	if (!ft_strcmp(((t_cmd *)cmd->data)->path, "echo")
		&& !ft_argcmp(((t_cmd *)cmd->data)->arg, "$_") && cmd->prev)
		lstcmd = cmd->prev->data;
	else if (!ft_strcmp(((t_cmd *)cmd->data)->path, "echo")
		&& !ft_argcmp(((t_cmd *)cmd->data)->arg, "$_"))
		lstcmd = NULL;
	else
		lstcmd = cmd->data;
	return (lstcmd);
}

void	ft_set_lstcmd(t_list *cmd)
{
	int		n;
	int		l;
	char	*lstcmd;
	t_cmd	*lcmd;
	char	*tmp;

	n = 0;
	l = 0;
	lcmd = get_lstcmd(cmd);
	if (lcmd)
	{
		n = ft_argsize(lcmd->arg) - 1;
		l = ft_strchrn(lcmd->arg[n], '=');
		if (!lcmd->arg[0])
			lstcmd = strdup("");
		else if (l)
			lstcmd = ft_substr(lcmd->arg[n], 0, l);
		else if (!(ft_strcmp(ft_strtolower(lcmd->arg[0]), "env")))
			lstcmd = ft_strdup(lcmd->path);
		else
			lstcmd = ft_strdup(lcmd->arg[n]);
		ht_replace(g_sh.env, ft_strdup("_"), lstcmd, 1, free);
	}
}