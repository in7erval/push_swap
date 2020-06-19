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

int check(t_stack *a, t_stack *b)
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

int is_undefined_operation(char *str)
{
	static char *operations[] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};
	int is_undef;
	int i;

	i = 0;
	is_undef = 1;
	while (i < 11)
	{
		if (ft_strcmp(str, operations[i]) == 0) {
			is_undef = 0;
			break;
		}
		i++;
	}
	return is_undef;
}

void	print_list(t_list *list)
{
	t_list *buf;

	buf = list;
	while (buf)
	{
		ft_putendl(buf->content);
		buf = buf->next;
	}
}

int main(int argc, char **argv)
{
	t_stack *a;
	t_stack	*b;
	char	*str;
	t_list *oprs;

	if (argc == 1)
		return 0;
	if (init_stacks(&a, &b, argc, argv))
		print_error("Error");
	if (check_duplicates(a))
	{
		free_stack(&a);
		print_error("Error");
	}
	oprs = NULL;
	while (get_next_line(0, &str)) {
		if (str == NULL || *str == 0)
			break;
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
	drawing(a, b, oprs);
	return (0);
}

/*
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
	} else {
		free_stack(&a);
		if (b->head)
			free_stack(&b);
		free(m);
		print_error("Error");
	}*/