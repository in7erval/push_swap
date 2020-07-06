/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:45:13 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 17:37:55 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			count_keep(t_stack *stack)
{
	t_elem	*buf;
	int		count;

	count = 0;
	if (stack->head)
	{
		buf = stack->head;
		if (buf->keep == 1)
			count++;
		buf = buf->next;
		while (buf != stack->head)
		{
			if (buf->keep == 1)
				count++;
			buf = buf->next;
		}
	}
	return (count);
}

t_elem		*create_elem(int value, int index, int keep)
{
	t_elem *new;

	new = (t_elem *)malloc(sizeof(t_elem));
	new->value = value;
	new->index = index;
	new->next = new;
	new->prev = new;
	new->keep = keep;
	return (new);
}

t_stack		*clone_stack(t_stack *a)
{
	t_stack	*clone;
	t_elem	*h;

	clone = (t_stack *)malloc(sizeof(t_stack));
	clone->size = 0;
	clone->head = NULL;
	h = a->head->prev;
	while (h != a->head)
	{
		add_front(clone, create_elem(h->value, h->index, h->keep));
		h = h->prev;
	}
	add_front(clone, create_elem(h->value, h->index, h->keep));
	return (clone);
}

int			try_to_sa(t_stack *a, int (*markup)(t_stack *, t_elem *))
{
	int		count1;
	int		count2;
	t_stack	*c;

	count1 = count_keep(a);
	c = clone_stack(a);
	swap(c, NULL, NULL);
	count2 = markup_all(c, markup);
	free_stack(&c);
	if (count2 > count1)
		return (1);
	return (0);
}

int			contains_not_keep(t_elem *head)
{
	t_elem *buf;

	if (head)
	{
		buf = head;
		if (buf->keep == -1)
			return (1);
		buf = buf->next;
		while (buf != head)
		{
			if (buf->keep == -1)
				return (1);
			buf = buf->next;
		}
	}
	return (0);
}
