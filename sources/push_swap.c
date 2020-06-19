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

void	check_solution(t_stack *a, t_stack *b, t_list *oprs)
{
	t_list *buf;
	char *str;

	buf = oprs;
	while (buf->next != NULL)
		buf = buf->next;
	while (buf) {
		str = buf->content;
		if (str == NULL || *str == 0)
			break;
		ft_printf("%s\n", str);
		if (ft_strcmp(str, "sa") == 0)
			swap(a, NULL, NULL);
		else if (ft_strcmp(str, "sb") == 0)
			swap(b, NULL, NULL);
		else if (ft_strcmp(str, "ss") == 0) {
			swap(a, NULL, NULL);
			swap(b, NULL, NULL);
		} else if (ft_strcmp(str, "pa") == 0)
			push(b, a, NULL, NULL);
		else if (ft_strcmp(str, "pb") == 0)
			push(a, b, NULL, NULL);
		else if (ft_strcmp(str, "ra") == 0)
			rotate(a, NULL, NULL);
		else if (ft_strcmp(str, "rb") == 0)
			rotate(b, NULL, NULL);
		else if (ft_strcmp(str, "rr") == 0) {
			rotate(a, NULL, NULL);
			rotate(b, NULL, NULL);
		} else if (ft_strcmp(str, "rra") == 0)
			reverse_rotate(a, NULL, NULL);
		else if (ft_strcmp(str, "rrb") == 0)
			reverse_rotate(b, NULL, NULL);
		else if (ft_strcmp(str, "rrr") == 0) {
			reverse_rotate(a, NULL, NULL);
			reverse_rotate(b, NULL, NULL);
		}
		print_stacks(a, b);

		getchar();
		buf = buf->prev;
	}
}

int main(int argc, char **argv)
{
	t_stack *a;
	t_stack *b;
	t_list	*oprs_g;
	t_list	*oprs_i;

	init_stacks(&a, &b, argc, argv);
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
	print_operations(count_nodes(oprs_g) > count_nodes(oprs_i) ? oprs_i : oprs_g);
	free_list(&oprs_g);
	free_list(&oprs_i);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
