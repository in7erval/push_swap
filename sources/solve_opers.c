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

int			count_closest(t_stack *a, t_elem *elem)
{
	t_elem	*buf;
	t_elem	*m;
	int		min;
	int		count;

	min = ft_abs(elem->index - a->head->index);
	buf = a->head->next;
	m = a->head;
	while (buf != a->head)
	{
		if (ft_abs(elem->index - buf->index) < min)
		{
			m = buf;
			min = ft_abs(elem->index - buf->index);
		}
		buf = buf->next;
	}
	count = 0;
	while (buf != m)
	{
		count++;
		buf = buf->next;
	}
	return (m->index < elem->index) ? count + 1 : count;
}

t_opr		count_opr_a(t_stack *a, t_elem *elem)
{
	t_opr	o;

	o.operator_a = RA;
	o.count_a = count_closest(a, elem);
	if (o.count_a > a->size / 2)
	{
		o.count_a = a->size - o.count_a;
		o.operator_a = RRA;
	}
	return (o);
}

t_opr		count_opr_b(t_stack *a, t_stack *b)
{
	t_elem		*buf;
	int			in_b;
	t_opr		min;
	t_opr		cur;

	min = count_opr_a(a, b->head);
	min.elem = b->head;
	min.count_b = 0;
	min.operator_b = RB;
	buf = b->head->next;
	in_b = 1;
	while (buf != b->head)
	{
		cur = count_opr_a(a, buf);
		cur.count_b = (in_b > (int)b->size / 2) ? (b->size - in_b) : in_b;
		cur.operator_b = (in_b > (int)b->size / 2) ? RRB : RB;
		if (cur.count_b + cur.count_a < min.count_b + min.count_a)
		{
			min = cur;
			min.elem = buf;
		}
		buf = buf->next;
		in_b++;
	}
	return (min);
}

static void	double_rotate_solve(t_opr *o, t_stack *a, t_stack *b, t_list **oprs)
{
	if (o->operator_b == RB && o->operator_a == RA)
		while (o->count_b > 0 && o->count_a > 0)
		{
			rotate(a, oprs, "rr");
			rotate(b, NULL, NULL);
			o->count_a--;
			o->count_b--;
		}
	if (o->operator_b == RRB && o->operator_a == RRA)
		while (o->count_b > 0 && o->count_a > 0)
		{
			reverse_rotate(a, oprs, "rrr");
			reverse_rotate(b, NULL, NULL);
			o->count_a--;
			o->count_b--;
		}
}

void		do_opr(t_opr o, t_stack *a, t_stack *b, t_list **oprs)
{
	double_rotate_solve(&o, a, b, oprs);
	while (o.count_b > 0)
	{
		if (o.operator_b == RB)
			rotate(b, oprs, "rb");
		else if (o.operator_b == RRB)
			reverse_rotate(b, oprs, "rrb");
		o.count_b--;
	}
	while (o.count_a > 0)
	{
		if (o.operator_a == RA)
			rotate(a, oprs, "ra");
		else if (o.operator_a == RRA)
			reverse_rotate(a, oprs, "rra");
		o.count_a--;
	}
	push(b, a, oprs, "pa");
}
