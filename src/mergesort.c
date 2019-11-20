#include "ls.h"

t_lsnode		*sortedmerge_list(t_lsnode *a, t_lsnode *b)
{
	t_lsnode	*result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->name, b->name) < 0)
	{
		result = a;
		result->next = sortedmerge_list(a->next, b);
	}
	else
	{
		result = b;
		result->next = sortedmerge_list(a, b->next);
	}
	return (result);
}

void		fbsplit_list(t_lsnode *source, t_lsnode **frontref, t_lsnode **backref)
{
	t_lsnode	*fast;
	t_lsnode	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}

void		mergesort_list(t_lsnode **list)
{
	t_lsnode	*head;
	t_lsnode	*a;
	t_lsnode	*b;

	head = *list;
	a = NULL;
	b = NULL;
	if ((head == NULL) || (head->next == NULL))
		return ;
	fbsplit_list(head, &a, &b);
	mergesort_list(&a);
	mergesort_list(&b);
	*list = sortedmerge_list(a, b);
}