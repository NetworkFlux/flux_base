#ifndef UNINSTALL_H
# define UNINSTALL_H

# define MAX_PATH_LENGTH 1024
# define MAX_USER_INPUT 1024
# define DEFAULT_PATH ".local/share/flux_base"
# define ENV_VAR "FLUX_DB_PATH"
# define TARGET_LINE "export FLUX_DB_PATH="

# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

#endif
