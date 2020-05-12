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

int 	count_keep(t_stack *stack)
{
	t_elem *buf;
	int count;

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
	return count;
}

t_stack *clone_stack(t_stack *a)
{
	t_stack *clone;
	t_elem *h;
	t_elem *new;

	clone = (t_stack *)malloc(sizeof(t_stack));
	clone->size = 0;
	h = a->head->prev;
	while (h != a->head)
	{
		new = (t_elem*)malloc(sizeof(t_elem));
		new->value = h->value;
		new->index = h->index;
		new->next = new;
		new->prev = new;
		new->keep = h->keep;
		add_front(clone, new);
		h = h->prev;
	}
	new = (t_elem*)malloc(sizeof(t_elem));
	new->value = h->value;
	new->index = h->index;
	new->next = new;
	new->prev = new;
	new->keep = h->keep;
	add_front(clone, new);
	return clone;
}

int 	try_to_sa(t_stack *a, int (*markup)(t_stack *, t_elem *))
{
	int count1;
	int count2;
	t_stack *c;

	count1 = count_keep(a);
	c = clone_stack(a);
	swap(c, NULL, NULL);
	count2 = markup_all(c, markup);
	free_stack(&c);
	if (count2 > count1)
		return 1;
	return 0;
}

int 	contains_not_keep(t_elem *head)
{
	t_elem *buf;

	if (head)
	{
		buf = head;
		if (buf->keep == -1)
			return 1;
		buf = buf->next;
		while (buf != head)
		{
			if (buf->keep == -1)
				return 1;
			buf = buf->next;
		}
	}
	return 0;
}

void	push_to_b(t_stack *a, t_stack *b, t_list **oprs, int (*markup)(t_stack *, t_elem *))
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

t_opr 	count_opr_a(t_stack *a, t_elem *elem)
{
	t_elem	*buf;
	t_elem	*m;
	int		min;
	t_opr	o;

	o.count_a = 0;
	o.operator_a = RA;
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
	while (buf != m)
	{
		o.count_a++;
		buf = buf->next;
	}
	if (m->index < elem->index)
		o.count_a++;
	if (o.count_a > a->size / 2)
	{
		o.count_a = a->size - o.count_a;
		o.operator_a = RRA;
	}
	return o;
}

t_opr	count_opr_b(t_stack *a, t_stack *b)
{
	t_elem *buf;
	int in_b;
	t_opr	min;
	t_opr 	cur;


	min = count_opr_a(a, b->head);
	min.elem = b->head;
	min.count_b = 0;
	min.operator_b = RB;
	buf = b->head->next;
	in_b = 1;
	while (buf != b->head)
	{
		cur = count_opr_a(a, buf);
		if (in_b > (int)b->size / 2)
		{
			cur.count_b = (b->size - in_b);
			cur.operator_b = RRB;
		}
		else
		{
			cur.count_b = in_b;
			cur.operator_b = RB;
		}
		if (cur.count_b + cur.count_a < min.count_b + min.count_a)
		{
			min = cur;
			min.elem = buf;
		}
		buf = buf->next;
		in_b++;
	}
	//ft_printf("opr_a:%d c_a:%d opr_b:%d c_b:%d %d %p\n", min.operator_a, min.count_a, min.operator_b, min.count_b, min.elem->value, min.elem);
	return min;
}

void	do_opr(t_opr o, t_stack *a, t_stack *b, t_list **oprs)
{
	if (o.operator_b == RB && o.operator_a == RA)
		while (o.count_b > 0 && o.count_a > 0)
		{
			rotate(a, oprs, "rr");
			rotate(b, NULL, NULL);
			o.count_a--;
			o.count_b--;
		}
	if (o.operator_b == RRB && o.operator_a == RRA)
		while (o.count_b > 0 && o.count_a > 0)
		{
			reverse_rotate(a, oprs, "rrr");
			reverse_rotate(b, NULL, NULL);
			o.count_a--;
			o.count_b--;
		}
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
void	align_a(t_stack *a, t_list **oprs)
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

t_list	*solve(t_stack *a, t_stack *b, int (*markup)(t_stack *, t_elem *))
{
	t_list *list_operations;

	list_operations = NULL;
	markup_all(a, markup);
	push_to_b(a, b, &list_operations, markup);

	while (b->size != 0)
		do_opr(count_opr_b(a, b), a, b, &list_operations);

	align_a(a, &list_operations);
	return list_operations;
}

int		markup_all(t_stack *a, int (*markup)(t_stack *, t_elem *))
{
	t_elem *max_markup;
	t_elem *cur_markup;
	int 	i;
	int max_i;

	max_i = 0;
	if (a && a->head)
	{
		cur_markup = a->head;
		max_markup = a->head;
		i = max_i = markup(a, cur_markup);
		cur_markup = cur_markup->next;
		while (cur_markup != a->head)
		{
			i = markup(a, cur_markup);
			if (i > max_i)
			{
				max_i = i;
				max_markup = cur_markup;
			}
			cur_markup = cur_markup->next;
		}
		a->markup = max_markup;
		markup(a, max_markup);
	}
	return  max_i;
}

int 	greater(t_stack *a, t_elem *markup_head)
{
	int	i;
	int	max;
	t_elem *beginning;

	i = 1;
	if (a && a->head && markup_head)
	{
		(void) a;
		markup_head->keep = 1;
		max = markup_head->value;
		beginning = markup_head;
		markup_head = markup_head->next;
		while (markup_head != beginning)
		{
			if (markup_head->value > max)
			{
				i++;
				max = markup_head->value;
				markup_head->keep = 1;
			}
			else
				markup_head->keep = -1;
			markup_head = markup_head->next;
		}
	}
	return i;
}

int		by_index(t_stack *a, t_elem *markup_head)
{
	size_t	index;
	int		i;
	t_elem *beginning;

	(void) a;
	i = 1;
	if (a && a->head && markup_head)
	{
		index = markup_head->index;
		markup_head->keep = 1;
		beginning = markup_head;
		markup_head = markup_head->next;
		while (markup_head != beginning)
		{
			if (markup_head->index == (index + 1))
			{
				index++;
				i++;
				markup_head->keep = 1;
			}
			else
				markup_head->keep = -1;
			markup_head = markup_head->next;
		}
	}
	return i;
}

void	put_indexes(t_stack *a)
{
	int *array;
	t_elem *buf;
	size_t i;

	i = 1;
	if (a && a->head)
	{
		array = (int *) malloc(sizeof(int) * a->size);
		array[0] = a->head->value;
		buf = a->head->next;
		while (buf != a->head)
		{
			array[i] = buf->value;
			buf = buf->next;
			i++;
		}
		sort_array(array, a->size);
		i = 0;
		while (i < a->size)
		{
			if (a->head->value == array[i])
				a->head->index = i;
			buf = a->head->next;
			while (buf != a->head)
			{
				if (buf->value == array[i])
				{
					buf->index = i;
					break;
				}
				buf = buf->next;
			}
			i++;
		}
		free(array);
	}
}

void	sort_array(int *array, int size) //todo: upgrade sort
{
	int i;
	int j;
	int buf;

	i = 0;
	while (i < size)
	{
		j = i;
		while (j < size)
		{
			if (array[i] > array[j])
			{
				buf = array[i];
				array[i] = array[j];
				array[j] = buf;
			}
			j++;
		}
		i++;
	}
}

