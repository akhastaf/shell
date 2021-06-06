/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:53:45 by akhastaf          #+#    #+#             */
/*   Updated: 2021/06/06 17:45:43 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdlib.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# define BUILTINS_NUM 7
# define UP 4283163
# define DOWN 4348699
# define DELETE 127

typedef int	t_fun_ptr(char **);

typedef struct s_ex
{
	char	*k;
	char	*v;
	int		n;
	int		ret;
}		t_ex;

typedef struct s_tc
{
	char			*name;
	struct termios	term;
	struct termios	init;
}					t_tc;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_key_value
{
	void	*key;
	void	*value;
}			t_key_value;

typedef struct s_hash_table
{
	size_t	lenght;
	t_list	**backets;
}	t_hash_table;

typedef struct s_red
{
	char	*type;
	char	*file;
}			t_red;

typedef struct s_cmd
{
	char	*path;
	char	**arg;
	t_list	*red;
	int		fdin;
	int		fdout;
	int		pipe[2];
}			t_cmd;

typedef struct s_pipeline
{
	char	*str;
	t_list	*cmd;
}			t_pipeline;

typedef struct s_sh
{
	t_list			*pipeline;
	t_hash_table	*env;
	t_hash_table	*builtins;
	char			*line;
	char			*tmp_line;
	t_tc			tc;
	t_list			*hist;
	t_list			*tmp_hist;
	int				status;
	int				in;
	int				out;
	char			**errors;
	char			*home;
	int				error;
	int				pid;
	int				is_pipe;
	char			*oldpwd;
	char			*pwd;
	int				is_pwd;
	int				is_oldpwd;
}					t_sh;
#endif
