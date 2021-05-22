/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:17:01 by akhastaf          #+#    #+#             */
/*   Updated: 2021/05/21 18:03:23 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int     main(int ac, char **av, char **env)
{
	init_sh(env);
	minishell_loop();
	return g_sh.status;
}

void	init_sh(char **env)
{
	init_env(env);
    init_builtins();
	init_errors();
	ft_set_pwd();
	g_sh.in = dup(0);
	g_sh.out = dup(1);
	g_sh.status = 0;
	g_sh.pid = 0;
	if (ft_checkenv("OLDPWD"))
		ht_delone(g_sh.env, "OLDPWD", 4, free);
	increment_shlvl();
}
void    init_env(char **env)
{
    size_t l;
    int i;
    int n;
    char    *key;
    char    *val;

    l = ft_argsize(env);
    init_hashtable(&(g_sh.env), l);
    i = 0;
    while (i < l)
    {
        n =ft_strchrn(env[i], '=');
        key = ft_strndup(env[i], n);
        val = ft_strdup(env[i] + n + 1);
        insert_to_table(g_sh.env, key, val, ft_strlen(key));
        i++;
    }
	// insert_to_table(g_sh.env, ft_strdup("A"), ft_strdup("ls | grep Makefile"), 1);
	// insert_to_table(g_sh.env, ft_strdup("B"), ft_strdup("f1\\ 2"), 1);
	insert_to_table(g_sh.env, ft_strdup("A"), ft_strdup("   aa   "), 1);
	insert_to_table(g_sh.env, ft_strdup("B"), ft_strdup("  bb  "), 1);
	insert_to_table(g_sh.env, ft_strdup("C"), ft_strdup("  cc  "), 1);
}

void    init_builtins(void)
{
    init_hashtable(&(g_sh.builtins), BUILTINS_NUM);
	insert_to_table(g_sh.builtins, ft_strdup("env"), builtins_env, 3);
	insert_to_table(g_sh.builtins, ft_strdup("echo"), builtins_echo, 4);
	insert_to_table(g_sh.builtins, ft_strdup("export"), builtins_export, 6);
	insert_to_table(g_sh.builtins, ft_strdup("unset"), builtins_unset, 5);
	insert_to_table(g_sh.builtins, ft_strdup("pwd"), builtins_pwd, 3);
	insert_to_table(g_sh.builtins, ft_strdup("exit"), builtins_exit, 4);
	insert_to_table(g_sh.builtins, ft_strdup("cd"), builtins_cd, 2);
}

int     count_backslash(char *str)
{
	int i;
	int j;
	int sq;

	sq = 0;
	i = ft_strlen(str) - 1;
	j = 0;
	while (i >= 0)
	{
		if (str[i] == '\'' && !sq)
			sq = 0;
		else if (str[i] == '\'' && sq)
			sq = 0;
		if (str[i] == '\\' && !sq)
			j++;
		else if (str[i] != '\\')
			break; 
		i--;
	}
	return j;
}


void	init_errors(void)
{
	g_sh.errors = malloc(sizeof(char*) * 11);
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

void	ft_set_pwd(void)
{
	char *pwd;
	char *lstcmd;
	
	if (!(pwd = ft_getenv("PWD")))
		if (!(pwd = getcwd(NULL, 0)))
			pwd = ft_strdup("");
	ht_replace(g_sh.env, ft_strdup("PWD"), pwd, 3, free);
}


void	increment_shlvl(void)
{
	int value;
	char *env;
	char *v;

	env = ft_getenv("SHLVL");
	value = ft_atoll(env ? env : "");
	free(env);
	if (value >= 2147483647)
		value = -1;
	if (value >= 200000)
	{
		printf("minishell: warning: shell level (%d) too high, resetting to 1", value + 1);
		value = 0;
	}
	else if (value < 0)
		value = -1;
	v = ft_itoa(value + 1);
	ht_replace(g_sh.env, ft_strdup("SHLVL"), v, 5, free);
}

void	ft_set_lstcmd(t_list *cmd)
{
	int n;
	int l;
	char *lstcmd;
	t_cmd *lcmd;
	char *tmp;

	n = 0;
	l = 0;
	if (cmd->next)
	{
		ht_delone(g_sh.env, "_", 1, free);
		return ;
	}
	if (!ft_strcmp(((t_cmd*)cmd->data)->path, "echo") 
			&& !ft_argcmp(((t_cmd*)cmd->data)->arg, "$_") && cmd->prev)
		lcmd = cmd->prev->data;
	else if (!ft_strcmp(((t_cmd*)cmd->data)->path, "echo") && !ft_argcmp(((t_cmd*)cmd->data)->arg, "$_"))
		lcmd = NULL;
	else
		lcmd = cmd->data;
	if (lcmd)
	{
		n = ft_argsize(lcmd->arg) - 1;
		if (!lcmd->arg[0])
			lstcmd = strdup("");
		else if (( l = ft_strchrn(lcmd->arg[n], '=')))
			lstcmd = ft_substr(lcmd->arg[n], 0, l);
		else if (!(ft_strcmp(ft_strtolower(lcmd->arg[0]), "env")))
			lstcmd = ft_strdup(lcmd->path);
		else
			lstcmd = ft_strdup(lcmd->arg[n]);
		ht_replace(g_sh.env, ft_strdup("_"), lstcmd, 1, free);
	}
}