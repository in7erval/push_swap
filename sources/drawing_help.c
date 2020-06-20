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

t_point	new_point(int x, int y, int color)
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

	if (p.x >= 0 && p.x < (int)m->width && p.y >= 0 && p.y < (int)m->height)
	{
		i = (p.x * m->bits_per_pixel / 8) + (p.y * m->size_line);
		m->data_addr[i] = p.color;
		m->data_addr[++i] = p.color >> 8;
		m->data_addr[++i] = p.color >> 16;
		m->data_addr[++i] = 0;
	}
}
