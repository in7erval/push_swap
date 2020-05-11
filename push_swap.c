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

int main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;
	t_list	*oprs_g;

	init_stacks(&a, &b, argc, argv);
	//print_stacks(a, b);
	oprs_g = solve(a, b, greater);
	//print_stacks(a, b);
	print_operations(oprs_g);
	ft_printf("Count: %d\n", count_nodes(oprs_g));
	free_list(&oprs_g);
	free_stacks(&a, &b);
	return (0);
}
