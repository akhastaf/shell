/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 12:41:13 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/20 17:31:57 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_export(void)
{
    t_list  *tmp;
    t_list  *env;
    char    *value;
    
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

static void check_var(char *var, char *arg, int *ret)
{
    if (ft_isdigit(var[0]) || ft_isstrnchr(var, " |!;&$@\\'\"") || ft_is_empty(var))
    {
        printf("minishell: export: `%s': not a valid identifier", arg);
        *ret = 1;
    }
}

int	builtins_export(char **arg)
{
	int		i;
	int		n;
	char	*var;
	char	*val;
	int		ret;
	char	*tmp;

	val = NULL;
	tmp = NULL;
	n = 0;
	ret = 0;
	if (ft_argsize(arg) == 1)
        print_export();
	i = 1;
    while (arg[i])
    {
        n = ft_strchrn(arg[i], '+');
        if (arg[i][0] == '=' || (n && n < ft_strchrn(arg[i], '=') && arg[i][n + 1]  != '='))
		{
            printf("minishell: export: `%s': not a valid identifier", arg[i]);
			ret = 1;
		}
        n = ft_strchrn(arg[i], '=');
        if (arg[i][ternary(n - 1 < 0, n, n - 1)] == '+')
        {
            var = ft_strndup(arg[i], n - 1);
            val = ft_getenv(var);
        }
        else if (n)
            var = ft_strndup(arg[i], n);
        else
            var = ft_strdup(arg[i]);
        val = ft_strjoin(val, arg[i] + n + 1);
        check_var(var, arg[i], &ret);
        if (!n && !ft_isstrnchr(var, " |!;&$@\\'\""))
            insert_to_table(g_sh.env, var, NULL, ft_strlen(var));
		else if (!ft_isstrnchr(var, " |!;&$@\\'\""))
            ht_add(g_sh.env, var, val, ft_strlen(var), free);
        i++;
		val = NULL;
    }
	return (ret);
}
