/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:50:21 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/29 15:55:24 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_hashtable(t_hash_table **ht, size_t lenght)
{
	size_t	i;

	*ht = malloc(sizeof(t_hash_table));
	if (!(*ht))
		return ;
	(*ht)->lenght = lenght;
	(*ht)->backets = malloc(sizeof(t_list *) * lenght);
	i = 0;
	while (i < lenght)
	{
		(*ht)->backets[i] = NULL;
		i++;
	}
}

unsigned int	hash_code(const void *key, int lenght)
{
	unsigned int	code;
	unsigned char	*k;
	size_t			i;
	size_t			size;

	i = 0;
	code = 0;
	if (!key)
		return (-1);
	size = ft_strlen(key);
	k = (unsigned char *)key;
	while (i < size)
	{
		code += (k[i] * k[i]) + 12;
		i++;
	}
	return (code % lenght);
}

void	insert_to_table(t_hash_table *ht, void *k, void *v, size_t size)
{
	unsigned int	id;
	t_list			*new;
	t_key_value		*kv;

	kv = malloc(sizeof(t_key_value));
	if (!kv)
		return ;
	kv->key = k;
	kv->value = v;
	new = ft_lstnew(kv);
	id = hash_code(k, ht->lenght);
	if (id == -1)
		return ;
	if (!ht->backets[id])
		ht->backets[id] = new;
	else
		ft_lstadd_back(&(ht->backets[id]), new);
}

void	*get_value(t_hash_table *ht, void *key)
{
	unsigned int	id;
	t_list			*tmp;

	id = hash_code(key, ht->lenght);
	if (id == -1)
		return (NULL);
	tmp = ht->backets[id];
	while (tmp)
	{
		if (!ft_strncmp(key, ((t_key_value *)tmp->data)->key,
				ft_strlen(((t_key_value *)tmp->data)->key))
			&& ((t_key_value *)tmp->data)->value)
			return (((t_key_value *)tmp->data)->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_key_value	*get_key_value(t_hash_table *ht, void *key)
{
	unsigned int	id;
	t_list			*tmp;

	id = hash_code(key, ht->lenght);
	if (id == -1)
		return (NULL);
	tmp = ht->backets[id];
	while (tmp)
	{
		if (!ft_strncmp(key, ((t_key_value *)tmp->data)->key,
				ft_strlen(((t_key_value *)tmp->data)->key)))
			return (((t_key_value *)tmp->data));
		tmp = tmp->next;
	}
	return (NULL);
}
