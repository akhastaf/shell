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

void    init_env(char **env);
#endif