#include "../../includes/minishell.h"

int		is_specialcar(char c)
{
	if (c == '"' || c == '\'' || c == '|' || c == '$' || c == '~' || c == ';' || c == '>' || c == '<')
		return 1;
	return 0;
}