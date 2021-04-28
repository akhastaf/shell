#include "../../includes/minishell.h"


int     ft_argsize(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
        i++;
    return i;
}