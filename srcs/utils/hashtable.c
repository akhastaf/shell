#include "../../includes/minishell.h"
#include <string.h>

void    init_hashtable(t_hash_table **ht, size_t lenght)
{
    size_t i;

    *ht = malloc(sizeof(t_hash_table));
    (*ht)->lenght = lenght;
    (*ht)->backets = malloc(sizeof(t_list *) * lenght);
    i = 0;
    while (i < lenght)
    {
        (*ht)->backets[i] = NULL;
        i++;
    }
}


unsigned int    hash_code(const void *key, int lenght)
{
    unsigned int code;
    unsigned char *k;
    size_t i;
    size_t size;

    i = 0;
    code = 0;
    if (!key)
        return -1;
    size = ft_strlen(key);
    k = (unsigned char *)key;
    while (i < size)
    {
        code += (k[i] * k[i]) + 12;
        i++;
    }
    return (code % lenght);
}

void    insert_to_table(t_hash_table *ht,void *k,void *v, size_t size)
{
    unsigned int id;
    t_list *new;
    t_key_value *kv;

    kv = malloc(sizeof(t_key_value));
    kv->key = k;
    kv->value = v;
    new = ft_lstnew(kv);
    id = hash_code(k, ht->lenght);
    if (id == -1)
        return ;
    if (!ht->backets[id])
        ht->backets[id] = new;
    else
        ft_lstadd_back(&(ht->backets[id]), new);
}

void     *get_value(t_hash_table *ht, void *key)
{
    unsigned int id;
    t_list *tmp;

    id = hash_code(key,ht->lenght);
    if (id == -1)
        return NULL;
    tmp = ht->backets[id];
    while (tmp)
    {
        if (!ft_strncmp(key, ((t_key_value *)tmp->data)->key, ft_strlen(((t_key_value *)tmp->data)->key)) && ((t_key_value *)tmp->data)->value)
        {
            return ((t_key_value *)tmp->data)->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

t_key_value     *get_key_value(t_hash_table *ht, void *key)
{
    unsigned int id;
    t_list *tmp;

    id = hash_code(key, ht->lenght);
    if (id == -1)
        return NULL;
    tmp = ht->backets[id];
    while (tmp)
    {
        if (!ft_strncmp(key, ((t_key_value *)tmp->data)->key, ft_strlen(((t_key_value *)tmp->data)->key)))
            return ((t_key_value *)tmp->data);
        tmp = tmp->next;
    }
    return NULL;
}

t_list          *get_keys(t_hash_table *ht)
{
    t_list  *new;
    t_list  *tmp;
    t_list *tmp1;
    size_t  i;

    new = NULL;

    tmp = NULL;
    i = 0;
    while (i < ht->lenght)
    {
        tmp = ht->backets[i];
        while (tmp && ((t_key_value*)tmp->data)->key)
        {
            tmp1 = ft_lstnew(ft_strdup(((t_key_value*)tmp->data)->key));
            ft_lstadd_back(&new, tmp1);
            tmp = tmp->next;
        }
        i++;
    }
    return new;
}

t_list          *get_values(t_hash_table *ht)
{
    t_list  *new;
    t_list  *tmp;
    t_list  *tmp1;
    size_t  i;

    new = NULL;
    tmp = NULL;
    i = 0;
    while (i < ht->lenght)
    {
        tmp = ht->backets[i];
        while (tmp && ((t_key_value*)tmp->data)->value)
        {
            tmp1 = ft_lstnew(((t_key_value*)tmp->data)->value);
            ft_lstadd_back(&new, tmp1);
            tmp = tmp->next;
        }
        i++;
    }
    return new;
}


void    print_ht(t_hash_table *ht)
{
    size_t i;
    t_list *tmp;

    i = 0;
    while (i < ht->lenght)
    {
        printf("%zu\n", i);
        if (ht->backets[i])
        {
            tmp = ht->backets[i];
            while (tmp)
            {
                printf("key : %s\tvalue : %s\n", (char*)((t_key_value*)tmp->data)->key, (char*)((t_key_value*)tmp->data)->value);
                tmp = tmp->next;
            }
        }
        i++;
    }
}


void    ht_replace(t_hash_table *ht, void *k, void *v, size_t size, void (*del)(void*))
{
    t_key_value *key_val;
    char *tmp;

    key_val = get_key_value(ht, k);
    if (key_val)
    {
        tmp = key_val->value;
        del(key_val->value);
        key_val->value = v;
        free(k);
    }
    else
        insert_to_table(ht, k, v, size);
}

void    ht_delone(t_hash_table *ht, void *k, size_t size, void (*del)(void*))
{
    unsigned int id;
    t_list *tmp;
    t_list *p;

    id = hash_code(k, ht->lenght);
    if (id == -1)
        return ;
    tmp = ht->backets[id];
    if (!ft_strncmp(k, ((t_key_value *)tmp->data)->key, ft_strlen(((t_key_value *)tmp->data)->key)))
    {
        ht->backets[id] = tmp->next;
        del(((t_key_value *)tmp->data)->key);
        del(((t_key_value *)tmp->data)->value);
        ft_lstdelone(tmp, del);
        return ;
    }
    else
    {
        while (tmp)
        {
            if (!ft_strncmp(k, ((t_key_value *)tmp->data)->key, ft_strlen(((t_key_value *)tmp->data)->key)))
            {
                if (tmp->prev)
                    tmp->prev->next = tmp->next;
                else
                {
                    tmp = tmp->next;
                    tmp->prev = NULL;
                }
                if (tmp->next)
                    tmp->next->prev = tmp->prev;
                else
                    tmp->prev->next = NULL;
                // p->next = tmp->next;
                del(((t_key_value *)tmp->data)->key);
                del(((t_key_value *)tmp->data)->value);
                //ft_lstdelone(tmp, del);
                tmp = NULL;
                break;
            }
            // p = tmp;
            tmp = tmp->next;
        }
    }
}

void    ht_add(t_hash_table *ht, void *k, void *v, size_t size, void (*del)(void*))
{
    if (get_value(ht, k))
        ht_replace(ht, k, v,size, del);
    else
        insert_to_table(ht, k, v, size);
}

int     count_table(t_hash_table *ht)
{
    t_list *tmp;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < ht->lenght)
    {
        tmp = ht->backets[i];
        while (tmp)
        {
            j++;
            tmp = tmp->next;
        }
        i++;
    }
    return j;
}
char    **ht_totable(t_hash_table *ht)
{
    int len;
    int i;
    char **t;
    t_list *tmp1;
    t_list *tmp2;

    tmp1 = get_keys(ht);
    tmp2 = get_values(ht);
    len = ft_lstsize(tmp1);
    t = malloc(sizeof(char*) * (len + 1));
    i = 0;
    while (i < len)
    {
        if (tmp1->data && tmp2->data)
        {
            t[i] = ft_strdup(tmp1->data);
            t[i] = ft_strappend(t[i], '=');
            t[i] = ft_strjoin(t[i], ft_strdup(tmp2->data));
            i++;
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    t[i] = NULL;
    return t;
}