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

void	double_swap(t_stack *a, t_stack *b)
{
	swap(a, NULL, NULL);
	swap(b, NULL, NULL);
}

void	double_rotate(t_stack *a, t_stack *b)
{
	rotate(a, NULL, NULL);
	rotate(b, NULL, NULL);
}

void	double_reverse_rotate(t_stack *a, t_stack *b)
{
	reverse_rotate(a, NULL, NULL);
	reverse_rotate(b, NULL, NULL);
}

int		check_all(char *str, t_stack *a, t_stack *b)
{
	if (ft_strcmp(str, "sa") == 0)
		swap(a, NULL, NULL);
	else if (ft_strcmp(str, "sb") == 0)
		swap(b, NULL, NULL);
	else if (ft_strcmp(str, "ss") == 0)
		double_swap(a, b);
	else if (ft_strcmp(str, "pa") == 0)
		push(b, a, NULL, NULL);
	else if (ft_strcmp(str, "pb") == 0)
		push(a, b, NULL, NULL);
	else if (ft_strcmp(str, "ra") == 0)
		rotate(a, NULL, NULL);
	else if (ft_strcmp(str, "rb") == 0)
		rotate(b, NULL, NULL);
	else if (ft_strcmp(str, "rr") == 0)
		double_rotate(a, b);
	else if (ft_strcmp(str, "rra") == 0)
		reverse_rotate(a, NULL, NULL);
	else if (ft_strcmp(str, "rrb") == 0)
		reverse_rotate(b, NULL, NULL);
	else if (ft_strcmp(str, "rrr") == 0)
		double_reverse_rotate(a, b);
	else
		return (1);
	return (0);
}
