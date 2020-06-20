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

int		main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;
	t_list	*oprs_g;
	t_list	*oprs_i;

	if (init_stacks(&a, &b, argc, argv))
		print_error("Error");
	if (check_duplicates(a))
	{
		free_stack(&a);
		print_error("Error");
	}
	oprs_g = solve(a, b, greater);
	free_stack(&a);
	free_stack(&b);
	init_stacks(&a, &b, argc, argv);
	oprs_i = solve(a, b, by_index);
	print_operations(count_nodes(oprs_g) > count_nodes(oprs_i)
	? oprs_i : oprs_g);
	free_list(&oprs_g);
	free_list(&oprs_i);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
