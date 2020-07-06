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

int			markup_all(t_stack *a, int (*markup)(t_stack *, t_elem *))
{
	t_elem	*max_markup;
	t_elem	*cur_markup;
	int		i;
	int		max_i;

	max_i = 0;
	if (a && a->head)
	{
		cur_markup = a->head;
		max_markup = a->head;
		i = markup(a, cur_markup);
		max_i = markup(a, cur_markup);
		cur_markup = cur_markup->next;
		while (cur_markup != a->head)
		{
			i = markup(a, cur_markup);
			max_i = (i > max_i) ? i : max_i;
			max_markup = (i == max_i) ? cur_markup : max_markup;
			cur_markup = cur_markup->next;
		}
		a->markup = max_markup;
		markup(a, max_markup);
	}
	return (max_i);
}

int			greater(t_stack *a, t_elem *markup_head)
{
	int		i;
	int		max;
	t_elem	*beginning;

	i = 1;
	if (a && a->head && markup_head)
	{
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
	return (i);
}

int			by_index(t_stack *a, t_elem *markup_head)
{
	size_t	index;
	int		i;
	t_elem	*beginning;

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
	return (i);
}

int			init_stack(t_stack **a, t_stack **b)
{
	if (!(*a = (t_stack *)malloc(sizeof(t_stack))))
		return (1);
	if (!(*b = (t_stack *)malloc(sizeof(t_stack))))
	{
		free(*a);
		return (1);
	}
	(*a)->size = 0;
	(*a)->head = NULL;
	(*b)->size = 0;
	(*b)->head = NULL;
	return (0);
}
