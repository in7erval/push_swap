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

void	free_list(t_list **list)
{
	t_list *node;

	if (list)
	{
		while (*list)
		{
			node = *list;
			(*list) = (*list)->next;
			free(node);
		}
		list = NULL;
	}
}

void	free_stack(t_stack **stack)
{
	t_elem *del;
	t_elem *buf;

	if ((*stack)->head && (*stack)->size > 0)
	{
		buf = (*stack)->head->next;
		while (buf != (*stack)->head)
		{
			del = buf;
			buf = buf->next;
			free(del);
		}
		free(buf);
	}
	free(*stack);
}

void	add_back(t_stack *stack, t_elem *elem)
{
	if (stack->head == NULL || stack->size == 0)
		stack->head = elem;
	else
	{
		stack->head->prev->next = elem;
		elem->prev = stack->head->prev;
		elem->next = stack->head;
		stack->head->prev = elem;
	}
	stack->size++;
}

t_elem	*new_element(int value)
{
	t_elem	*e;

	e = (t_elem *)malloc(sizeof(t_elem));
	e->value = value;
	e->prev = e;
	e->next = e;
	e->keep = -1;
	e->index = 0;
	return (e);
}

void	add_front(t_stack *stack, t_elem *elem)
{
	if (stack == NULL)
		return ;
	if (stack->head == NULL || stack->size == 0)
		stack->head = elem;
	else
	{
		stack->head->prev->next = elem;
		elem->prev = stack->head->prev;
		elem->next = stack->head;
		stack->head->prev = elem;
		stack->head = elem;
	}
	stack->size++;
}
