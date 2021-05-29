/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:43:17 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/29 15:45:32 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*get_keys(t_hash_table *ht)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmp1;
	size_t	i;

	new = NULL;
	tmp = NULL;
	i = 0;
	while (i < ht->lenght)
	{
		tmp = ht->backets[i];
		while (tmp && ((t_key_value *)tmp->data)->key)
		{
			tmp1 = ft_lstnew(ft_strdup(((t_key_value *)tmp->data)->key));
			ft_lstadd_back(&new, tmp1);
			tmp = tmp->next;
		}
		i++;
	}
	return (new);
}

t_list	*get_values(t_hash_table *ht)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmp1;
	size_t	i;

	new = NULL;
	tmp = NULL;
	i = 0;
	while (i < ht->lenght)
	{
		tmp = ht->backets[i];
		while (tmp && ((t_key_value *)tmp->data)->value)
		{
			tmp1 = ft_lstnew(((t_key_value *)tmp->data)->value);
			ft_lstadd_back(&new, tmp1);
			tmp = tmp->next;
		}
		i++;
	}
	return (new);
}
