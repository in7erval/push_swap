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

static	int check(t_stack *a, t_stack *b)
{
	int		i;
	t_elem	*elem;

	i = 1;
	if (b->size != 0)
		return 0;
	if (a->head->next->value < a->head->value)
		return 0;
	elem = a->head->next;
	while (elem != a->head)
	{
		if (elem->value < elem->prev->value)
			return 0;
		elem = elem->next;
	}
	return 1;
}

int main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	char	*str;
	int		i = 0;

	if (argc == 1)
		return (0);
	init_stacks(&a, &b, argc, argv);
	while (get_next_line(0, &str)) {
		if (str == NULL || *str == 0)
			break;
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
		free(str);
		i++;
		//print_stacks(a, b);
	}
	free(str);
	//print_stacks(a, b);
	if (check(a, b) == 1)
		ft_putendl("OK");
	else
		ft_putendl("KO");
	//ft_printf("Count: %d\n", i);
	free_stacks(&a, &b);
	return (0);
}

