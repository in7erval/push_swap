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

void	put_color(t_stack *stack, int color_from, int color_to, int max_index)
{
	t_elem *cur;

	cur = stack->head;
	if (cur != NULL)
	{
		cur->color = get_color(color_from, color_to,
				(float)cur->index / (float)max_index);
		cur = cur->next;
		while (cur != stack->head)
		{
			cur->color = get_color(color_from, color_to,
					(float)cur->index / (float)max_index);
			cur = cur->next;
		}
	}
}

void	put_colors(t_mlx *m)
{
	put_color(m->a, m->color_from, m->color_to, m->max_index);
	put_color(m->b, m->color_from, m->color_to, m->max_index);
}
