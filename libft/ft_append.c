#include "libft.h"

void	ft_append(t_list **alst, t_list *new)
{
	t_list	*curr;

	if (!new || !alst)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}
