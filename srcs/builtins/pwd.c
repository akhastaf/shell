/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:41:09 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 15:54:28 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtins_pwd(char **arg)
{
	char	*pwd;

	(void)arg;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_getenv("PWD");
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
