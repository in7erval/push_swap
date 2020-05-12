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

void 	print_error(char *s)
{
	ft_putendl(s);
	exit(1);
}

int 	ft_abs(int i)
{
	return i < 0 ? -i : i;
}

void	print_operations(t_list *oprs)
{
	t_list *first;

	if (!oprs)
		return;
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
	return i;
}

void	free_list(t_list **list)
{
	t_list *node;

	if (list)
	{
		while (*list)
		{
			node = *list;
			(*list) = (*list)->next;
			free(node);
		}
		list = NULL;
	}
}

void	free_stack(t_stack **stack)
{
	t_elem *del;
	t_elem *buf;

	if ((*stack)->head && (*stack)->size > 0)
	{
		buf = (*stack)->head->next;
		while (buf != (*stack)->head)
		{
			del = buf;
			buf = buf->next;
			free(del);
		}
		free(buf);
	}
	free(*stack);
}

void	add_back(t_stack *stack, t_elem *elem)
{
	if (stack->head == NULL || stack->size == 0)
		stack->head = elem;
	else
	{
		stack->head->prev->next = elem;
		elem->prev = stack->head->prev;
		elem->next = stack->head;
		stack->head->prev = elem;
	}
	stack->size++;
}

t_elem *new_element(int value)
{
	t_elem	*e;

	e = (t_elem *)malloc(sizeof(t_elem));
	e->value = value;
	e->prev = e;
	e->next = e;
	e->keep = -1;
	e->index = 0;
	return e;
}

void	add_front(t_stack *stack, t_elem *elem)
{
	if (stack->head == NULL || stack->size == 0)
		stack->head = elem;
	else
	{
		stack->head->prev->next = elem;
		elem->prev = stack->head->prev;
		elem->next = stack->head;
		stack->head->prev = elem;
		stack->head = elem;
	}
	stack->size++;
}

void	add_n_operations(t_list *oprs, int n, char *str)
{
	while (n-- > 0)
		ft_lstadd(&oprs, ft_lstnew(str, 0));
}

void	init_stacks(t_stack **a, t_stack **b, int argc, char **argv)
{
	int i;
	char **split;

	if (argc == 1)
		print_error("Error");
	*a = (t_stack *)malloc(sizeof(t_stack));
	*b = (t_stack *)malloc(sizeof(t_stack));
	i = argc - 1;
	(*a)->size = 0;
	(*b)->size = 0;
	if (argc == 2)
	{
		i = count_words(argv[1], ' ') - 1;
		split = ft_strsplit(argv[1], ' ');
		while (i >= 0)
		{
			add_front(*a, new_element(ft_atoi(split[i])));
			free(split[i]);
			i--;
		}
		free(split);
	} else
		while (i-- > 0)
			add_front(*a, new_element(ft_atoi(argv[i--])));
	put_indexes(*a);
}

t_elem	*pop(t_stack *stack)
{
	t_elem *a;

	a = NULL;
	if (stack)
	{
		a = stack->head;
		stack->head->prev->next = stack->head->next;
		stack->head->next->prev = stack->head->prev;
		stack->head = stack->head->next;
		stack->size--;
		a->next = a;
		a->prev = a;
	}
	return a;
}

void	print_stack_debug(t_stack *stack)
{
	t_elem *buf;

	buf = stack->head;
	ft_printf("PRINT STACK DEBUG %p\n", stack->head);
	if (buf->keep == -1)
		ft_printf("%2d {magenta}index:%2d keep:%+d {red}cur:%14p {green}next:%14p {yellow}prev:%14p{eoc}\n", buf->value, buf->index, buf->keep, buf, buf->next, buf->prev);
	else
		ft_printf("{cyan}%2d {magenta}index:%2d {cyan}keep:%+d {red}cur:%14p {green}next:%14p {yellow}prev:%14p{eoc}\n", buf->value, buf->index, buf->keep, buf, buf->next, buf->prev);
	buf = buf->next;
	while (buf != stack->head)
	{
		if (buf->keep == -1)
			ft_printf("%2d {magenta}index:%2d keep:%+d {red}cur:%14p {green}next:%14p {yellow}prev:%14p{eoc}\n", buf->value, buf->index, buf->keep, buf, buf->next, buf->prev);
		else
			ft_printf("{cyan}%2d {magenta}index:%2d {cyan}keep:%+d {red}cur:%14p {green}next:%14p {yellow}prev:%14p{eoc}\n", buf->value, buf->index, buf->keep, buf, buf->next, buf->prev);
		buf = buf->next;
	}
	ft_printf("\n");
}

void	print_stack(t_stack *stack)
{
	t_elem *buf;

	ft_printf("%d\n", stack->head->value);
	buf = stack->head->next;
	while (buf != stack->head)
	{
		ft_printf("%d\n", buf->value);
		buf = buf->next;
	}
	ft_printf("\n");
}


void	print_stacks(t_stack *a, t_stack *b)
{
	t_elem *elem_a;
	t_elem *elem_b;
	size_t i;

	elem_a = a->head;
	elem_b = b->head;
	int max = find_max(elem_a, elem_b);
	int max_digits = ft_count_of_digits(max);
	i = a->size > b->size ? a->size : b->size;
	do { //todo: create func print_line, print_line<––>print_dashes
		if (a->size >= i && b->size >= i) {
			ft_printf("%*d", max_digits, elem_a->value);
			print_line(elem_a->value, '-');
			print_space(elem_a->value, max);
			ft_printf("%*d", max_digits, elem_b->value);
			print_line(elem_b->value, '-');
		}
		else if (a->size >= i)
		{
			ft_printf("%*d", max_digits, elem_a->value);
			print_line(elem_a->value, '-');
		}
		else if (b->size >= i)
		{
			print_line(max + ft_count_of_digits(max) + 3, ' ');
			ft_printf("%*d", max_digits, elem_b->value);
			print_line(elem_b->value, '-');
		}
		ft_putchar('\n');
		elem_a = (a->size >= i) ? elem_a->next : elem_a;
		elem_b = (b->size >= i) ? elem_b->next : elem_b;
		i--;
	} while (elem_a != a->head || elem_b != b->head);
	ft_putchar('\n');
	//ft_printf("–––   –––\n a     b \n\n");
}

int		find_max(t_elem *a, t_elem *b)
{
	t_elem *buf;
	int max;

	max = 0;
	if (a)
	{
		max = a->value;
		buf = a->next;
		while (buf != a)
		{
			if (buf->value > max)
				max = buf->value;
			buf = buf->next;
		}
	}
	if (b)
	{
		max = (b->value > max) ? b->value : max;
		buf = b->next;
		while (buf != b)
		{
			if (buf->value > max)
				max = buf->value;
			buf = buf->next;
		}
	}
	return max;
}

void	print_line(int a, char c)
{
	int i = 0;
	while (i < a)
	{
		ft_putchar(c);
		i++;
	}
}

void	print_space(int a, int max)
{
	int spaces = max - a + 3;
	int i = 0;

	while (i < spaces)
	{
		ft_putchar(' ');
		i++;
	}
}

int		count_words(const char *str, char c)
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

void	ft_lstaddnew(t_list **list, char *str)
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