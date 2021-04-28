#ifndef MINISHELL_H
# define MINISHELL_H

#include "./struct.h"
#include "./utils.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>

t_sh    g_sh;

// SHELL INIT
void	init_sh(char **env);
void    init_env(char **env);
void    init_builtins(void);
void	init_errors(void);
void	increment_shlvl(void);

// Excutions
int     warp_excute(t_pipeline *p);
int     excute();
// PROCESSE
void    init_pipeline(void);
void    process_pipeline(t_pipeline *p);
char    *ft_refactor_line(char *s);


// MINISHELL
void    minishell_loop(void);

// REDIRECTIONS
t_list   *get_redirection(char *cmd);
char    *remove_red(char *cmd);
char    *ft_getword(char *word, char *set);

// UTILS
void    print_pipeline(void);

// BUILTINS
int	    builtins_env(char **arg);
int	    builtins_pwd(char **arg);
int     builtins_unset(char **arg);
int     builtins_echo(char **arg);
int     builtins_cd(char **arg);
int     builtins_export(char **arg);
int     builtins_exit(char **arg);

// ENV
char    *ft_getenv(char *var);
char    *ft_getpath(char *file);
int     ft_isbuiltins(char *path);
void	ft_set_pwd(void);


// GNL
void	setup_term(void);
void	get_printable(long c);
int     gnl_term(void);
int     putchar_tc(int c);
void	backspace(void);
void	handle_keys(long c);
void	ft_free(char **s);
void	add_hist(char *s);
void	up_hist(void);
void	line_form_hist(void);
void	backedup_line(void);
void	down_hist(void);

// PIPE
void    delete_pipe(void *p);
void    delete_cmd(void *cmd);
void    delete_red(void *red);
#endif