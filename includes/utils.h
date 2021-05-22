#ifndef UTILS_H
# define UTILS_H
#include "./struct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int     count_backslash(char *str);
// LINKEDLIST
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *data);
int		ft_lstsize(t_list *lst);
void	ft_lstprint(t_list *lst);
void	sort_list(t_list **lst);


// HASHTABLE
void            init_hashtable(t_hash_table **ht, size_t lenght);
void            insert_to_table(t_hash_table *ht,void *k,void *v, size_t size);
void            *get_value(t_hash_table *ht, void *key);
t_key_value     *get_key_value(t_hash_table *ht, void *key);
t_list          *get_keys(t_hash_table *ht);
t_list          *get_values(t_hash_table *ht);
void            clear_hashtable(t_hash_table **ht, void (*del)(void*));
void    ht_replace(t_hash_table *ht, void *k, void *v, size_t size, void (*del)(void*));
void            ht_delone(t_hash_table *ht, void *k, size_t size, void (*del)(void*));
void            ht_add(t_hash_table *ht, void *k, void *v, size_t size, void (*del)(void*));
void            print_ht(t_hash_table *ht);
char    **ht_totable(t_hash_table *ht);


//UTILS
char		*ft_strjoin(char  *s1, char  *s2);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
size_t      ft_strlen(char const *str);
char		*ft_strndup(const char *s1, size_t n);
char	*ft_checkerror(int fd, char **buff);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
char    *ft_strappend(char *str, char c);
char    *ft_strrepace(char *str);
int     ft_argsize(char **arg);
char    **ft_argadd(char **arg, char *var);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void    print_arg(char **arg);
void    ft_delete_arg(char **arg);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_is_space(char c);
char			*ft_itoa(int n);
int     ft_strchrn(char *s, char c);
char    **ft_argtrim(char **arg, char *set);
// char				**ft_split(char const *s, char c);
char				**ft_split(char const *s, char *set);
int     ft_countcahr(char *s, char c);
int     ft_strnchrn(char *s, char *set);
int		is_specialcar(char c);
int     ft_count_space(char *s);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
char     *ft_strnchr(char *s, char *set);
int     ft_is_empty(char *s);
void	*ft_memdel(void *ptr);
int		ft_tolower(int c);
char *ft_strtolower(char *str);
long long		ft_atoll(const char *str);
int     ft_strisdigit(char *str);
int     ft_isstrnchr(char *s, char *set);
int     ft_argcmp(char **arg, char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void    ft_puterror(char *f, char *ar, char *l);
void    ft_argprint(char **arg);
int	ternary(int condition, int ret1, int ret2);
void    ft_argmap(char ***arg, char *(*map)(char *));
#endif