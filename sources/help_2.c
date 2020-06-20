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

static int	find_max_in_stack(t_elem *stack)
{
	t_elem	*buf;
	int		max;

	max = 0;
	if (stack)
	{
		max = stack->value;
		buf = stack->next;
		while (buf != stack)
		{
			if (buf->value > max)
				max = buf->value;
			buf = buf->next;
		}
	}
	return (max);
}

int			find_max(t_elem *a, t_elem *b)
{
	int		max1;
	int		max2;

	max1 = find_max_in_stack(a);
	max2 = find_max_in_stack(b);
	return (max1 > max2 ? max1 : max2);
}

int			count_words(const char *str, char c)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str != c)
			if (*(str + 1) == c || *(str + 1) == '\0')
				i++;
		str++;
	}
	return (i);
}

void		ft_lstaddnew(t_list **list, char *str)
{
	t_list *cur;

	if (!(*list))
		*list = ft_lstnew(str, 0);
	else
	{
		cur = ft_lstnew(str, 0);
		cur->next = (*list);
		(*list)->prev = cur;
		(*list) = cur;
	}
}

int			ft_isnumber(char *str)
{
	int i;

	i = 0;
	if (*str == '-' && *(str + 1) != 0 && ft_isdigit(*(str + 1)))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
