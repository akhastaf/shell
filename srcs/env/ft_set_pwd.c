/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 17:41:01 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 16:14:27 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_set_pwd(void)
{
	char	*pwd;

	pwd = ft_getenv("PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			pwd = ft_strdup("");
	}
	ht_replace(g_sh.env, ft_strdup("PWD"), pwd);
}
