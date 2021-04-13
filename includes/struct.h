#ifndef STRUCT_H
# define STRUCT_H

# define BUILTINS_NUM 7

typedef int fun_ptr(char **);

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


typedef struct  s_pipeline
{
	char	*path;
	char	**arg;
	char	*opr;
	t_list	*red;
	int		fdin;
	int		fdout;
	int		pipe[2];
}		t_pipeline;


typedef struct s_sh
{
	t_list	*pipeline;
	t_hash_table *env;
	t_hash_table *builtins;
	// fun_ptr *builtins_fun[BUILTINS_NUM];
    // char    *builtins_str[BUILTINS_NUM];
	char	*line;
	t_list	*history;
	int		status;
	int		in;
	int		out;
	char	*errors;
	char	*home;
}		t_sh;
#endif