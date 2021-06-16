/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:41:13 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/16 15:47:35 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(char **arg)
{
	t_list	*tmp;
	t_list	*env;
	char	*value;

	if (ft_argsize(arg) != 1)
		return ;
	value = NULL;
	env = get_keys(g_sh.env);
	sort_list(&env);
	tmp = env;
	while (tmp)
	{
		if (tmp->data)
			value = get_value(g_sh.env, tmp->data);
		printe(value, tmp->data);
		tmp = tmp->next;
	}
	ft_lstclear(&env, free);
}

static void	check_var(t_ex *ex, char *arg, int *ret)
{
	char	*tmp;

	ex->n = ft_strchrn(arg, '=');
	tmp = ex->v;
	if (ex->n)
		ex->v = ft_strjoin(ex->v, arg + ex->n + 1);
	free(tmp);
	if (ft_isdigit(ex->k[0]))
	{
		ft_puterror("minishell: export: `", arg, "': not a valid identifier");
		*ret = 1;
	}
	if (!ft_strcmp(ex->k, "OLDPWD"))
		g_sh.is_oldpwd = 1;
	if (!ft_strcmp(ex->k, "PWD"))
		g_sh.is_pwd = 1;
}

static void	check_plus(char **arg, int i, char **var, char **val)
{
	int	n;

	n = ft_strchrn(arg[i], '=');
	if (arg[i][ternary(n - 1 < 0, n, n - 1)] == '+')
	{
		*var = ft_strndup(arg[i], n - 1);
		*val = ft_getenv(*var);
	}
	else if (n)
		*var = ft_strndup(arg[i], n);
	else
		*var = ft_strdup(arg[i]);
}

static int	check_validarg(char *arg, t_ex *ex)
{
	int		n;
	char	*key;

	ex->n = ft_strchrn(arg, '+');
	n = ft_strchrn(arg, '=');
	if (n)
		key = ft_strndup(arg, n);
	else
		key = ft_strdup(arg);
	if (!ft_isvalidarg(key) || key[0] == '+' || ft_is_empty(key))
	{
		ft_puterror("minishell: export: `", arg, "': not a valid identifier");
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

int	builtins_export(char **arg)
{
	int		i;
	t_ex	ex;
	char	*tmp;

	init_export(&tmp, &ex);
	print_export(arg);
	i = 0;
	while (arg[++i])
	{
		if (check_validarg(arg[i], &ex))
			ex.ret = 1;
		check_plus(arg, i, &(ex.k), &(ex.v));
		check_var(&ex, arg[i], &(ex.ret));
		if (ft_isvalidarg(ex.k))
		{
			if (!ex.n && !get_value(g_sh.env, ex.k))
				ex.v = NULL;
			ht_replace(g_sh.env, ex.k, ex.v);
		}
		else
			free_ex(ex.k, ex.v);
		ex.v = NULL;
	}
	return (ex.ret);
}
