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

int		is_undefined_operation(char *str)
{
	static char	*operations[] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb",
								"rr", "rra", "rrb", "rrr"};
	int			is_undef;
	int			i;

	i = 0;
	is_undef = 1;
	while (i < 11)
	{
		if (ft_strcmp(str, operations[i]) == 0)
		{
			is_undef = 0;
			break ;
		}
		i++;
	}
	return (is_undef);
}

int		check(t_stack *a, t_stack *b)
{
	int		i;
	t_elem	*elem;

	i = 1;
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

t_list	*do_oprs_checker_visual(t_stack *a, t_stack *b)
{
	char	*str;
	t_list	*oprs;

	oprs = NULL;
	while (get_next_line(0, &str))
	{
		if (str == NULL || *str == 0)
			break ;
		if (is_undefined_operation(str))
		{
			free_stack(&a);
			if (b->head)
				free_stack(&b);
			free_list(&oprs);
			print_error("Error");
		}
		ft_lstadd(&oprs, ft_lstnew(str, 0));
	}
	return (oprs);
}

int		main(int argc, char **argv)
{
	t_stack *a;
	t_stack	*b;
	t_list	*oprs;

	if (argc == 1)
		return (0);
	if (init_stacks(&a, &b, argc, argv))
		print_error("Error");
	if (check_duplicates(a))
	{
		free_stack(&a);
		print_error("Error");
	}
	oprs = do_oprs_checker_visual(a, b);
	drawing(a, b, oprs);
	return (0);
}
