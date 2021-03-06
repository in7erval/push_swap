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

void	print_error(char *s)
{
	ft_putendl(s);
	exit(1);
}

int		ft_abs(int i)
{
	return (i < 0 ? -i : i);
}

void	print_operations(t_list *oprs)
{
	t_list *first;

	if (!oprs)
		return ;
	first = oprs;
	while (oprs->next != NULL)
		oprs = oprs->next;
	while (oprs != first)
	{
		ft_putendl(oprs->content);
		oprs = oprs->prev;
	}
	ft_putendl(oprs->content);
}

size_t	count_nodes(t_list *oprs)
{
	t_list *node;
	size_t i;

	i = 0;
	node = oprs;
	while (node)
	{
		node = node->next;
		i++;
	}
	return (i);
}
