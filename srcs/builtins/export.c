/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:41:13 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/25 19:29:11 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(void)
{
	t_list	*tmp;
	t_list	*env;
	char	*value;

	value = NULL;
	env = get_keys(g_sh.env);
	sort_list(&env);
	tmp = env;
	while (tmp)
	{
		if (tmp->data)
			value = get_value(g_sh.env, tmp->data);
		if (value)
			printf("declare -x %s=\"%s\"\n", tmp->data, value);
		else
			printf("declare -x %s\n", tmp->data);
		tmp = tmp->next;
	}
}

static void	check_var(char *var, char *arg, int *ret)
{
	if (ft_isdigit(var[0]) || ft_isstrnchr(var, " -|!;&$@\\'\"")
		|| ft_is_empty(var))
	{
		printf("minishell: export: `%s': not a valid identifier", arg);
		*ret = 1;
	}
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

static void	check_validarg(char *arg, t_ex *ex)
{
	if (arg[0] == '=' || (ex->n && ex->n < ft_strchrn(arg, '=')
			&& arg[ex->n + 1] != '='))
	{
		printf("minishell: export: `%s': not a valid identifier", arg);
		ex->ret = 1;
	}
}

int	builtins_export(char **arg)
{
	int		i;
	t_ex	ex;
	t_kv	e;
	char	*tmp;

	init_export(&e, &tmp, &ex);
	if (ft_argsize(arg) == 1)
		print_export();
	i = -1;
	while (arg[++i])
	{
		ex.n = ft_strchrn(arg[i], '+');
		check_validarg(arg[i], &ex);
		check_plus(arg, i, &(e.k), &(e.v));
		tmp = e.v;
		e.v = ft_strjoin(e.v, arg[i] + ex.n + 1);
		free(tmp);
		check_var(e.k, arg[i], &(ex.ret));
		if (!(ex.n) && !ft_isstrnchr(e.k, " |!;&$@\\'\""))
			insert_to_table(g_sh.env, e.k, NULL, ft_strlen(e.k));
		else if (!ft_isstrnchr(e.k, " |!;&$@\\'\""))
			ht_add(g_sh.env, e.k, e.v, ft_strlen(e.k), free);
		e.v = NULL;
	}
	return (ex.ret);
}
