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

void		push_to_b(t_stack *a, t_stack *b, t_list **oprs,
		int (*markup)(t_stack *, t_elem *))
{
	t_elem *buf;

	buf = a->head;
	while (contains_not_keep(a->head))
	{
		if (try_to_sa(a, markup))
		{
			swap(a, oprs, "sa");
			markup_all(a, markup);
		}
		else if (a->head->keep == -1)
			push(a, b, oprs, "pb");
		else
			rotate(a, oprs, "ra");
	}
}

void		align_a(t_stack *a, t_list **oprs)
{
	t_opr rotating;

	rotating = (t_opr){.count_a = 0, .operator_a = RA};
	while (a->head->index != 0)
	{
		rotate(a, NULL, NULL);
		rotating.count_a++;
	}
	if (rotating.count_a > a->size / 2)
	{
		rotating.count_a = a->size - rotating.count_a;
		rotating.operator_a = RRA;
	}
	while (rotating.count_a-- > 0)
		if (rotating.operator_a == RA)
			ft_lstaddnew(oprs, "ra");
		else
			ft_lstaddnew(oprs, "rra");
}

t_list		*solve(t_stack *a, t_stack *b, int (*markup)(t_stack *, t_elem *))
{
	t_list *list_operations;

	list_operations = NULL;
	markup_all(a, markup);
	push_to_b(a, b, &list_operations, markup);
	while (b->size != 0)
		do_opr(count_opr_b(a, b), a, b, &list_operations);
	align_a(a, &list_operations);
	return (list_operations);
}
