#include "ls.h"

void    list_pop(t_lsnode *node)
{
    if (node->name)
        free(node->name);
    node->next = NULL;
    free(node);
}

void    list_push(t_lsnode **head, char *name, char *path)
{
    t_lsnode *new;

    if (!(new = ft_memalloc(sizeof(*new))))
        return ;
    new->name = ft_strdup(name);
    new->fullpath = path ? ls_makename(path, name) : ft_strdup(name);
    new->next = *head;
    *head = new;
}

void    list_insert(t_lsnode **curr, char *name, char *path)
{
    t_lsnode *new = NULL;
    list_push(&new, name, path);
    if (!*curr)
    {
        *curr = new;
        return ;
    }
    new->next = (*curr)->next;
    (*curr)->next = new;
}