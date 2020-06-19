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

void		mlx_hooks(t_mlx *m)
{
	mlx_hook(m->win, 17, 0, exit_program, m);
	mlx_hook(m->win, 2, 0, deal_key, m);
}

int		get_light(int start, int end, float percentage)
{
	return ((1 - percentage) * start + percentage * end);
}

int		get_color(int color1, int color2, float percent)
{
	int r;
	int g;
	int b;

	r = get_light((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, percent);
	g = get_light((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, percent);
	b = get_light(color1 & 0xFF, color2 & 0xFF, percent);
	return ((r << 16) + (g << 8) + b);
}

t_point		new_point(int x, int y, int color)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.color = color;
	return (p);
}

void	put_pixel(t_mlx *m, t_point p)
{
	int	i;

	if (p.x >= 0 && p.x < (int) m->width && p.y >= 0 && p.y < (int) m->height)
	{
		i = (p.x * m->bits_per_pixel / 8) + (p.y * m->size_line);
		m->data_addr[i] = p.color;
		m->data_addr[++i] = p.color >> 8;
		m->data_addr[++i] = p.color >> 16;
		m->data_addr[++i] = 0;
	}
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

int			deal_key(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	if ((keycode == KEY_ENTER || keycode == KEY_RIGHT) && mlx->oprs)
		draw_stacks(mlx);
	//if ((keycode == KEY_LEFT || keycode == KEY_DELETE) && mlx->oprs)
	//	draw_stacks(mlx, 1);
	return (keycode);
}

int			exit_program(void *param)
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
	return max;
}

t_mlx *drawing_init(t_stack *a, t_stack *b, t_list *oprs)
{
	t_mlx	*m;
	t_list *last;

	m = (t_mlx *)malloc(sizeof(t_mlx));
	m->mlx = mlx_init();
	m->max_index = find_max_index(a);
	m->width = (m->max_index > 200) ? WIDTH * 1.5 : WIDTH;
	m->height = (m->max_index > 200) ? HEIGHT * 1.5 : HEIGHT;
	m->win = mlx_new_window(m->mlx, m->width, m->height, "PUSH_SWAP");
	m->img = mlx_new_image(m->mlx, m->width, m->height);
	m->data_addr = mlx_get_data_addr(m->img, &(m->bits_per_pixel),
									 &(m->size_line), &(m->endian));
	ft_bzero(m->data_addr, m->width * m->height * (m->bits_per_pixel / 8));
	m->a = a;
	m->b = b;
	m->oprs = oprs;
	last = oprs;
	while (last->next)
		last = last->next;
	m->cur = last;
	m->max_index = find_max_index(a);
	m->color_from = DARK_TURQUOISE;
	m->color_to = VIOLET;
	put_colors(m);
	return m;
}

void	drawing(t_stack *a, t_stack *b, t_list *oprs)
{
	t_mlx	*m;

	m = drawing_init(a, b, oprs);
	mlx_hooks(m);
	mlx_loop(m->mlx);
}

void 	draw_stack(t_mlx *m, t_stack *stack, int x, int height)
{
	t_elem *head;
	int y;

	put_rectangle(m, new_point(x, 0, stack->head->color), ((stack->head->index + 1) *m->width / 2) / (m->max_index + 1), height);
	head = stack->head->next;
	y = height;
	while (head != stack->head)
	{
		put_rectangle(m, new_point(x, y, head->color), ((head->index + 1) * m->width / 2) / (m->max_index + 1), height);
		y += height;
		head = head->next;
	}
}

void	do_operation(t_mlx *m)
{
	char *str;

	str = (m->cur) ? m->cur->content : NULL;
	if (str == NULL || *str == 0)
		return;
	if (ft_strcmp(str, "sa") == 0)
		swap(m->a, NULL, NULL);
	else if (ft_strcmp(str, "sb") == 0)
		swap(m->b, NULL, NULL);
	else if (ft_strcmp(str, "ss") == 0) {
		swap(m->a, NULL, NULL);
		swap(m->b, NULL, NULL);
	} else if (ft_strcmp(str, "pa") == 0)
		push(m->b, m->a, NULL, NULL);
	else if (ft_strcmp(str, "pb") == 0)
		push(m->a, m->b, NULL, NULL);
	else if (ft_strcmp(str, "ra") == 0)
		rotate(m->a, NULL, NULL);
	else if (ft_strcmp(str, "rb") == 0)
		rotate(m->b, NULL, NULL);
	else if (ft_strcmp(str, "rr") == 0) {
		rotate(m->a, NULL, NULL);
		rotate(m->b, NULL, NULL);
	} else if (ft_strcmp(str, "rra") == 0)
		reverse_rotate(m->a, NULL, NULL);
	else if (ft_strcmp(str, "rrb") == 0)
		reverse_rotate(m->b, NULL, NULL);
	else if (ft_strcmp(str, "rrr") == 0) {
		reverse_rotate(m->a, NULL, NULL);
		reverse_rotate(m->b, NULL, NULL);
	}
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
	height = m->height / count;
	draw_stack(m, m->a, 0, height);
	if (m->b->size > 0)
		draw_stack(m, m->b, m->width / 2, height);
	else
		put_rectangle(m, new_point(m->width / 2, 0, 0), m->width / 2, m->height);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}