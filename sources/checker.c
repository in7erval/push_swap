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

int		check(t_stack *a, t_stack *b)
{
	t_elem	*elem;

	if (b->size != 0)
		return (0);
	if (a->head->next->value < a->head->value)
		return (0);
	elem = a->head->next;
	while (elem != a->head)
	{
		if (elem->value < elem->prev->value)
			return (0);
		elem = elem->next;
	}
	return (1);
}

void	do_oprs_checker(t_stack *a, t_stack *b)
{
	char	*str;

	while (get_next_line(0, &str))
	{
		if (str == NULL || *str == 0)
			break ;
		if (check_all(str, a, b) == 1)
		{
			free_stack(&a);
			if (b->head)
				free_stack(&b);
			free(str);
			print_error("Error");
		}
		free(str);
	}
	free(str);
}

int		main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	if (init_stacks(&a, &b, argc, argv))
		print_error("Error");
	if (check_duplicates(a))
	{
		free_stack(&a);
		print_error("Error");
	}
	do_oprs_checker(a, b);
	if (check(a, b) == 1)
		ft_putendl("OK");
	else
		ft_putendl("KO");
	free_stack(&a);
	free_stack(&b);
	return (0);
}
