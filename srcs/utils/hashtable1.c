/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:42:12 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 17:04:43 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ht_replace(t_hash_table *ht, void *k, void *v, size_t size)
{
	t_key_value	*key_val;
	char		*tmp;

	key_val = get_key_value(ht, k);
	if (key_val)
	{
		tmp = key_val->value;
		free(key_val->value);
		key_val->value = v;
		free(k);
	}
	else
		insert_to_table(ht, k, v, size);
}

void	ht_delone(t_hash_table *ht, void *k, size_t size, void (*del)(void*))
{
	unsigned int	id;
	t_list			*tmp;
	t_list			*p;

	id = hash_code(k, ht->lenght);
	if (id == -1)
		return ;
	tmp = ht->backets[id];
	if (!ft_strncmp(k, ((t_key_value *)tmp->data)->key,
			ft_strlen(((t_key_value *)tmp->data)->key)))
	{
		ht->backets[id] = tmp->next;
		del(((t_key_value *)tmp->data)->key);
		del(((t_key_value *)tmp->data)->value);
		ft_lstdelone(tmp, del);
		return ;
	}
	else
		ht_delmultiple(tmp, k, del);
}

void	ht_add(t_hash_table *ht, void *k, void *v, size_t size)
{
	if (get_value(ht, k))
		ht_replace(ht, k, v, size);
	else
		insert_to_table(ht, k, v, size);
}

int	count_table(t_hash_table *ht)
{
	t_list	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < ht->lenght)
	{
		tmp = ht->backets[i];
		while (tmp)
		{
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	return (j);
}

char	**ht_totable(t_hash_table *ht)
{
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = get_keys(ht);
	tmp2 = get_values(ht);
	return (ft_lst_totable(tmp1, tmp2));
}
