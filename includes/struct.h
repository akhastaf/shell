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


typedef int fun_ptr(char **);


typedef struct s_tc
{
	char			*name;
	struct termios	term;
	struct termios	init;
	char			*cm;
	char			*ce;
	char			*dl;
}				t_tc;

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
	
}					t_list;

typedef struct s_key_value
{
    void    *key;
    void    *value;
}   t_key_value;


typedef struct s_hash_table
{
    size_t         lenght;
    t_list      **backets;
}   t_hash_table;


typedef struct s_red
{
	char	*type;
	char	*file;
}	t_red;


typedef struct  s_cmd
{
	char	*path;
	char	**arg;
	char	*opr;
	t_list	*red;
	int		fdin;
	int		fdout;
	int		pipe[2];
}		t_cmd;

typedef struct s_pipeline
{
	char	*str;
	t_list *cmd;
}	t_pipeline;


typedef struct s_sh
{
	t_list	*pipeline;
	t_hash_table *env;
	t_hash_table *builtins;
	char		*line;
	char		*tmp_line;
	t_tc		tc;
	t_list		*hist;
	t_list		*tmp_hist;
	long long	status;
	int			in;
	int			out;
	char		**errors;
	char		*home;
}				t_sh;
#endif