#include "../../includes/minishell.h"

void	ft_free(char **s)
{
	free(*s);
	*s = NULL;
}