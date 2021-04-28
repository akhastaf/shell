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


unsigned int    hash_code(const void *key, size_t   size, int lenght)
{
    unsigned int code;
    unsigned char *k;
    size_t i;

    i = 0;
    code = 0;
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
    id = hash_code(k, size, ht->lenght);
    if (!ht->backets[id])
        ht->backets[id] = new;
    else
        ft_lstadd_back(&(ht->backets[id]), new);
}

void     *get_value(t_hash_table *ht, void *key, size_t size)
{
    unsigned int id;
    t_list *tmp;

    id = hash_code(key, size, ht->lenght);
    tmp = ht->backets[id];
    while (tmp)
    {
        if (!ft_memcmp(key, ((t_key_value *)tmp->data)->key, size))
            return ((t_key_value *)tmp->data)->value;
        tmp = tmp->next;
    }
    return NULL;
}

t_key_value     *get_key_value(t_hash_table *ht, void *key, size_t size)
{
    unsigned int id;
    t_list *tmp;

    id = hash_code(key, size, ht->lenght);
    tmp = ht->backets[id];
    while (tmp)
    {
        if (!ft_memcmp(key, ((t_key_value *)tmp->data)->key, size))
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
        while (tmp)
        {
            tmp1 = ft_lstnew(((t_key_value*)tmp->data)->key);
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
        while (tmp)
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

    key_val = get_key_value(ht, k, size);
    if (key_val)
    {
        tmp = key_val->value;
        del(key_val->value);
        key_val->value = v;
    }
    else
        insert_to_table(ht, k, v, size);
}

void    ht_delone(t_hash_table *ht, void *k, size_t size, void (*del)(void*))
{
    unsigned int id;
    t_list *tmp;
    t_list *p;

    id = hash_code(k, size, ht->lenght);
    tmp = ht->backets[id];
    p = tmp;
    while (tmp)
    {
        if (!ft_memcmp(k, ((t_key_value *)tmp->data)->key, size))
        {
            del(((t_key_value *)tmp->data)->key);
            del(((t_key_value *)tmp->data)->value);
            p->next = tmp->next;
            ft_lstdelone(tmp, del);
            tmp = NULL;
            break;
        }
        p = tmp;
        tmp = tmp->next;
    }
}

void    ht_add(t_hash_table *ht, void *k, void *v, size_t size, void (*del)(void*))
{
    if (get_value(ht, k, size))
    {
        ht_replace(ht, k, v,size, del);
        free(k);
    }
    else
        insert_to_table(ht, k, v, size);
}