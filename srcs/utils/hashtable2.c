/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:43:17 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 17:23:53 by akhastaf         ###   ########.fr       */
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

void	ht_delmultiple(t_list *tmp, void *k, void (*del)(void*))
{
	while (tmp)
	{
		if (!ft_strncmp(k, ((t_key_value *)tmp->data)->key,
				ft_strlen(((t_key_value *)tmp->data)->key)))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
			{
				tmp = tmp->next;
				tmp->prev = NULL;
			}
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			else
				tmp->prev->next = NULL;
			del(((t_key_value *)tmp->data)->key);
			del(((t_key_value *)tmp->data)->value);
			tmp = NULL;
			break ;
		}
		tmp = tmp->next;
	}
}
