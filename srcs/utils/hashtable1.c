/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:42:12 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/29 15:50:04 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ht_replace(t_hash_table *ht, void *k, void *v, size_t size, void (*del)(void*))
{
	t_key_value	*key_val;
	char		*tmp;

	key_val = get_key_value(ht, k);
	if (key_val)
	{
		tmp = key_val->value;
		del(key_val->value);
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
	if (!ft_strncmp(k, ((t_key_value *)tmp->data)->key, ft_strlen(((t_key_value *)tmp->data)->key)))
	{
		ht->backets[id] = tmp->next;
		del(((t_key_value *)tmp->data)->key);
		del(((t_key_value *)tmp->data)->value);
		ft_lstdelone(tmp, del);
		return ;
	}
	else
	{
		while (tmp)
		{
			if (!ft_strncmp(k, ((t_key_value *)tmp->data)->key, ft_strlen(((t_key_value *)tmp->data)->key)))
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
}

void	ht_add(t_hash_table *ht, void *k, void *v, size_t size, void (*del)(void*))
{
	if (get_value(ht, k))
		ht_replace(ht, k, v, size, del);
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
	int		len;
	int		i;
	char	**t;
	t_list	*tmp1;
	t_list	*tmp2;

	tmp1 = get_keys(ht);
	tmp2 = get_values(ht);
	len = ft_lstsize(tmp1);
	t = malloc(sizeof(char *) * (len + 1));
	if (!t)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (tmp1->data && tmp2->data)
		{
			t[i] = ft_strdup(tmp1->data);
			t[i] = ft_strappend(t[i], '=');
			t[i] = ft_strjoin(t[i], ft_strdup(tmp2->data));
			i++;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	t[i] = NULL;
	return (t);
}
