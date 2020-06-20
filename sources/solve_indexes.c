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

static void	sort_array(int *array, int size)
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

static int	*stack_to_array(t_stack *a)
{
	int		*array;
	t_elem	*buf;
	int		i;

	i = 1;
	array = (int *)malloc(sizeof(int) * a->size);
	array[0] = a->head->value;
	buf = a->head->next;
	while (buf != a->head)
	{
		array[i] = buf->value;
		buf = buf->next;
		i++;
	}
	return (array);
}

static void	put_index(t_stack *a, int value, int index)
{
	t_elem *buf;

	if (a->head->value != value)
	{
		buf = a->head->next;
		while (buf != a->head)
		{
			if (buf->value == value)
			{
				buf->index = index;
				break ;
			}
			buf = buf->next;
		}
	}
	else
		a->head->index = index;
}

void		put_indexes(t_stack *a)
{
	int		*array;
	size_t	i;

	if (a && a->head)
	{
		array = stack_to_array(a);
		sort_array(array, a->size);
		i = 0;
		while (i < a->size)
		{
			put_index(a, array[i], i);
			i++;
		}
		free(array);
	}
}
