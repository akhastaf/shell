/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:37:57 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/01 17:10:07 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	swap(t_list *a, t_list *b)
{
	char	*temp;

	temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void	sort_list(t_list **lst)
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = *lst;
	while (tmp)
	{
		tmp1 = *lst;
		while (tmp1)
		{
			if (tmp1->next && ft_strcmp(tmp1->data, tmp1->next->data) >= 0)
				swap(tmp1, tmp1->next);
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
}

char	**ft_lst_totable(t_list *tmp1, t_list *tmp2)
{
	char	**t;
	int		len;
	int		i;

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
