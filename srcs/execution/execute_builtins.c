/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:46:32 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/26 15:50:43 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtins(char *path, char **arg)
{
	t_fun_ptr	*f;

	f = get_value(g_sh.builtins, path);
	g_sh.status = f(arg);
}
