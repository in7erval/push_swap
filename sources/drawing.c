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

t_mlx	*drawing_init(t_stack *a, t_stack *b, t_list *oprs)
{
	t_mlx	*m;

	m = (t_mlx *)malloc(sizeof(t_mlx));
	m->mlx = mlx_init();
	m->max_index = find_max_index(a);
	m->width = (m->max_index) >= WIDTH ? m->max_index / 2 : WIDTH;
	m->height = (m->max_index < HEIGHT) ? HEIGHT : m->max_index + 1;
	m->win = mlx_new_window(m->mlx, m->width, m->height, "PUSH_SWAP");
	m->img = mlx_new_image(m->mlx, m->width, m->height);
	m->data_addr = mlx_get_data_addr(m->img, &(m->bits_per_pixel),
	&(m->size_line), &(m->endian));
	ft_bzero(m->data_addr, m->width * m->height * (m->bits_per_pixel / 8));
	m->a = a;
	m->b = b;
	m->oprs = oprs;
	m->max_index = find_max_index(a);
	m->max_index = m->max_index == 0 ? 1 : m->max_index;
	m->color_from = DARK_TURQUOISE;
	m->color_to = VIOLET;
	put_colors(m);
	m->cur = oprs;
	while (m->cur && m->cur->next)
		m->cur = m->cur->next;
	return (m);
}

void	drawing(t_stack *a, t_stack *b, t_list *oprs)
{
	t_mlx	*m;

	m = drawing_init(a, b, oprs);
	mlx_hooks(m);
	mlx_loop(m->mlx);
}

void	draw_stack(t_mlx *m, t_stack *stack, int x, int height)
{
	t_elem	*head;
	int		y;
	int		width;

	width = (stack->head->index == 0 ?
			 (1 * m->width) / 2 : (stack->head->index * m->width)) / (2 * m->max_index);
	put_rectangle(m, new_point(x, 0, stack->head->color), width, height);
	head = stack->head->next;
	y = height;
	while (head != stack->head)
	{
		width = (head->index == 0 ?
				(1 * m->width) / 2 : (head->index * m->width)) / (2 * m->max_index);
		put_rectangle(m, new_point(x, y, head->color), width, height);
		y += height;
		head = head->next;
	}
}

void	do_operation(t_mlx *m)
{
	char *str;

	str = (m->cur) ? m->cur->content : NULL;
	if (str == NULL || *str == 0)
		return ;
	check_all(str, m->a, m->b);
	if (m->cur != NULL)
		m->cur = m->cur->prev;
}

void	draw_stacks(t_mlx *m)
{
	int count;
	int height;

	ft_bzero(m->data_addr, m->width * m->height * (m->bits_per_pixel / 8));
	do_operation(m);
	count = m->a->size + m->b->size;
	height = (int) ((m->height * 1.0f) / count);
	draw_stack(m, m->a, 0, height);
	if (m->b->size > 0)
		draw_stack(m, m->b, m->width / 2, height);
	else
		put_rectangle(m, new_point(m->width / 2, 0, 0),
		m->width / 2, m->height);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}
