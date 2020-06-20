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

void	mlx_hooks(t_mlx *m)
{
	mlx_hook(m->win, 17, 0, exit_program, m);
	mlx_hook(m->win, 2, 0, deal_key, m);
}

void	put_rectangle(t_mlx *m, t_point p, int width, int height)
{
	t_point draw;

	draw = p;
	while (draw.y < p.y + height)
	{
		draw.x = p.x;
		while (draw.x < p.x + width)
		{
			put_pixel(m, draw);
			draw.x++;
		}
		draw.y++;
	}
}

int		deal_key(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	if ((keycode == KEY_ENTER || keycode == KEY_RIGHT) && mlx->oprs)
		draw_stacks(mlx);
	return (keycode);
}

int		exit_program(void *param)
{
	t_mlx *m;

	m = (t_mlx *)param;
	if (check(m->a, m->b) == 1)
		ft_putendl("OK");
	else
		ft_putendl("KO");
	free_stack(&(m->a));
	if (m->b->head)
		free_stack(&(m->b));
	free_list(&(m->oprs));
	free(param);
	exit(0);
}

size_t	find_max_index(t_stack *a)
{
	t_elem *cur;
	size_t max;

	cur = a->head;
	max = cur->index;
	cur = cur->next;
	while (cur != a->head)
	{
		if (cur->index > max)
			max = cur->index;
		cur = cur->next;
	}
	return (max);
}
