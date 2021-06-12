/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:17:01 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/12 18:03:43 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_sh(env);
	minishell_loop();
	return (g_sh.status);
}

void	init_sh(char **env)
{
	init_env(env);
	init_builtins();
	init_errors();
	ft_set_pwd();
	g_sh.home = getenv("HOME");
	g_sh.in = dup(0);
	g_sh.out = dup(1);
	g_sh.status = 0;
	g_sh.pid = -1;
	g_sh.pipeline = NULL;
	g_sh.error = 0;
	g_sh.is_oldpwd = 1;
	g_sh.is_pwd = 1;
	g_sh.oldpwd = NULL;
	g_sh.pwd = NULL;
	increment_shlvl();
}

void	init_env(char **env)
{
	size_t	l;
	size_t	i;
	int		n;
	char	*key;
	char	*val;

	l = ft_argsize(env);
	init_hashtable(&(g_sh.env), l);
	i = 0;
	while (i < l)
	{
		n = ft_strchrn(env[i], '=');
		key = ft_strndup(env[i], n);
		if (!ft_strncmp("OLDPWD", key, 6))
			val = NULL;
		else
			val = ft_strdup(env[i] + n + 1);
		insert_to_table(g_sh.env, key, val);
		i++;
	}
	if (!is_key(g_sh.env, "OLDPWD"))
		insert_to_table(g_sh.env, ft_strdup("OLDPWD"), NULL);
}

void	init_builtins(void)
{
	init_hashtable(&(g_sh.builtins), BUILTINS_NUM);
	insert_to_table(g_sh.builtins, ft_strdup("env"), builtins_env);
	insert_to_table(g_sh.builtins, ft_strdup("echo"), builtins_echo);
	insert_to_table(g_sh.builtins, ft_strdup("export"), builtins_export);
	insert_to_table(g_sh.builtins, ft_strdup("unset"), builtins_unset);
	insert_to_table(g_sh.builtins, ft_strdup("pwd"), builtins_pwd);
	insert_to_table(g_sh.builtins, ft_strdup("exit"), builtins_exit);
	insert_to_table(g_sh.builtins, ft_strdup("cd"), builtins_cd);
}

void	init_errors(void)
{
	g_sh.errors = malloc(sizeof(char *) * 11);
	if (!g_sh.errors)
		return ;
	g_sh.errors[1] = ft_strdup("minishell: syntax error token `|'");
	g_sh.errors[2] = ft_strdup("minishell: syntax error token `;'");
	g_sh.errors[3] = ft_strdup("minishell: syntax error token `||'");
	g_sh.errors[4] = ft_strdup("minishell: syntax error token `;;'");
	g_sh.errors[5] = ft_strdup("minishell: syntax error token  `|;'");
	g_sh.errors[6] = ft_strdup("minishell: syntax error token `;|'");
	g_sh.errors[7] = ft_strdup("minishell: syntax error token `<<'");
	g_sh.errors[8] = ft_strdup("minishell: syntax error token `>'");
	g_sh.errors[9] = ft_strdup("minishell: syntax error token `newline'");
	g_sh.errors[10] = ft_strdup("minishell: syntax error multiline");
}
