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

void 		put_colors(t_mlx *m)
{
	t_elem *cur;

	cur = m->a->head;
	if (cur != NULL)
	{
		cur->color = get_color(m->color_from, m->color_to, (float) cur->index / (float) m->max_index);
		cur = cur->next;
		while (cur != m->a->head)
		{
			cur->color = get_color(m->color_from, m->color_to, (float) cur->index / (float) m->max_index);
			cur = cur->next;
		}
	}
	cur = m->b->head;
	if (cur != NULL)
	{
		cur->color = get_color(m->color_from, m->color_to, (float) cur->index / (float) m->max_index);
		cur = cur->next;
		while (cur != m->a->head)
		{
			cur->color = get_color(m->color_from, m->color_to, (float) cur->index / (float) m->max_index);
			cur = cur->next;
		}
	}
}
