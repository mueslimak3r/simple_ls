#include "ls.h"

char				*ls_makename(char *s1, char *s2)
{
	char			*str;
	char			*ret;

	if (!s1)
		s1 = ".";
	str = (char *)ft_memalloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 2));
	if (str == NULL)
		return (NULL);
	ret = str;
	while (*s1)
		*(str++) = *(s1++);
	if (*(s1 - 1) != '/')
		*(str++) = '/';
	while (*s2)
		*(str++) = *(s2++);
	return (ret);
}

int     isdir(t_lsnode *contents_node)
{
    struct stat tmp;
    lstat(contents_node->fullpath, &tmp);
    if (S_ISDIR(tmp.st_mode))
        return (1);
    return (0);
}

void    print_and_add(t_lsnode *node, t_lsnode *contents)
{
    t_lsnode *curr_pos = node;
    printf("\n%s:\n", node->fullpath);
    while (contents)
    {
        printf("%s\n", contents->name);
        if (isdir(contents) && ft_strcmp(contents->name, ".") != 0 && ft_strcmp(contents->name, "..") != 0)
        {
            list_insert(&curr_pos, contents->name, node->fullpath);
            curr_pos = curr_pos->next;
        }
        t_lsnode *tmp = contents;
        contents = contents->next;
        list_pop(tmp);
    }
}

t_lsnode    *get_contents(DIR **pdir, t_lsnode *node)
{
    t_lsnode *contents = NULL;
    struct dirent	*pdirent;
    *pdir = opendir(node->fullpath);
    if (!*pdir)
        return (NULL);
    while (*pdir && (pdirent = readdir(*pdir)) != NULL)
    {
        list_push(&contents, pdirent->d_name, node->fullpath);
    }
    return (contents);
}

void    goto_dir(t_lsnode *node)

{
    t_lsnode  *dir_contents = NULL;
    DIR     *pdir = NULL;
    dir_contents = get_contents(&pdir, node);
    if (!dir_contents)
        return ;
    mergesort_list(&dir_contents);
    print_and_add(node, dir_contents);
    if (pdir)
        closedir(pdir);
}

void    travel(t_lsnode *list)
{
    while (list)
    {
        goto_dir(list);
        t_lsnode *tmp = list;
        list = list->next;
        list_pop(tmp);
    }
}

int main(int ac, char **av)
{
    t_lsnode *list = NULL;
    int i = 1;
    if (ac < 2)
        list_push(&list, ".", NULL);
    else
    {
        while (i < ac)
            list_push(&list, av[i++], NULL);
    }
    mergesort_list(&list);
    travel(list);
    return (0);
}