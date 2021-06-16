/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:14:19 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/16 15:44:44 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./struct.h"
# include "./utils.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>

t_sh		g_sh;
void		init_sh(char **env);
void		init_env(char **env);
void		init_builtins(void);
void		init_errors(void);
void		increment_shlvl(void);
void		signals(int sig);
void		execute(void);
void		magic_box(t_pipeline *p);
void		execute_builtins(char *path, char **arg);
void		check_execute_errors(t_cmd *cmd, int err);
void		init_pipeline(void);
void		process_pipeline(t_pipeline *p);
char		*ft_refactor_line(char *s);
char		*ft_tilde(char *s, char *line, int i);
char		*ft_putbackslash(char *s, int j);
char		*ft_keepq(char *s);
char		*ft_strremove(char *s, char c);
void		minishell_loop(void);
void		setup_redirection(t_cmd *cmd);
t_list		*get_redirection(char *cmd);
char		*remove_red(char *cmd);
char		*ft_getword(char *word, char *set);
int			get_option(t_red *red);
void		print_pipeline(void);
int			builtins_env(char **arg);
int			builtins_pwd(char **arg);
int			builtins_unset(char **arg);
int			builtins_echo(char **arg);
int			builtins_cd(char **arg);
int			builtins_exit(char **arg);
int			builtins_export(char **arg);
int			check_varenv(char *var);
void		init_export(char **tmp, t_ex *ex);
void		printe(char *v, char *data);
void		free_ex(char *k, char *v);
char		*ft_getenv(char *var);
int			ft_checkenv(char *var);
char		*ft_getpath(char *file, int i);
int			ft_isbuiltins(char *path);
void		ft_set_pwd(void);
void		setup_term(void);
void		get_printable(long c);
int			gnl_term(void);
int			putchar_tc(int c);
void		backspace(void);
void		handle_keys(long c);
void		add_hist(char *s);
void		up_hist(void);
void		line_form_hist(void);
void		backedup_line(void);
void		down_hist(void);
void		setup_pipe(t_list *cmd);
void		reset_std(void);
void		close_pipe(t_pipeline *p);
void		open_pipes(t_pipeline *p);
void		delete_pipe(void *p);
void		delete_cmd(void *cmd);
void		delete_red(void *red);
int			count_doubleq(char *str);
int			count_singleq(char *str);
int			check_quote(void);
int			check_red(void);
int			check_forbiden(void);
int			check_pipe(void);
char		*check_syntax(void);
void		ft_set_lstcmd(t_list *cmd);
void		signals(int sig);
#endif
