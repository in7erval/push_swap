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

void	push(t_stack *from, t_stack *to, t_list **oprs, char *str)
{
	t_elem *elem;

	if (from->size > 0 && from->head != NULL)
	{
		elem = pop(from);
		add_front(to, elem);
		if (oprs)
			ft_lstaddnew(oprs, str);
	}
}

void	swap(t_stack *stack, t_list **oprs, char *str)
{
	t_elem *top;
	t_elem *top_next;

	if (stack->size == 2)
	{
		rotate(stack, NULL, NULL);
		if (oprs)
			ft_lstaddnew(oprs, str);
		return;
	}
	top = pop(stack);
	top_next = pop(stack);
	add_front(stack, top);
	add_front(stack, top_next);
	if (oprs)
		ft_lstaddnew(oprs, str);
}

void	reverse_rotate(t_stack *stack, t_list **oprs, char *str)
{
	if (!stack || stack->size == 1 || stack->size == 0)
		return ;
	stack->head = stack->head->prev;
	if (oprs)
		ft_lstaddnew(oprs, str);
}

void	rotate(t_stack *stack, t_list **oprs, char *str)
{
	if (!stack || stack->size == 0 || stack->size == 1)
		return ;
	stack->head = stack->head->next;
	if (oprs)
		ft_lstaddnew(oprs, str);
}

