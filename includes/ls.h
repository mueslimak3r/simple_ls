#ifndef LS_H
#define LS_H

# include <stdio.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <stdbool.h>
# include <grp.h>
# include <pwd.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <time.h>
# include <sys/xattr.h>
# include "libft.h"
# include "ft_malloc.h"
typedef struct s_lsnode t_lsnode;

struct s_lsnode
{
    char    *name;
    char    *fullpath;
    t_lsnode  *next;
};

void        mergesort_list(t_lsnode **list);
void        list_push(t_lsnode **head, char *name, char *path);
void        list_insert(t_lsnode **curr, char *name, char *path);
void        list_pop(t_lsnode *node);
char		*ls_makename(char *s1, char *s2);
#endif
