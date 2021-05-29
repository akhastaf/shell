/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 14:06:27 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/26 14:12:18 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_option(t_red *red)
{
	int	option;

	option = 0;
	if (red->type && red->type[0] == '>' && red->type[1] != '>')
		option = O_CREAT | O_WRONLY | O_TRUNC;
	else if (red->type && red->type[0] == '<')
		option = O_RDONLY;
	else if (red->type && !ft_strcmp(red->type, ">>"))
		option = O_CREAT | O_WRONLY | O_APPEND;
	return (option);
}
