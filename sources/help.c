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

int 	ft_isnumber(char *str)
{
	int i;

	i = 0;
	if (*str == '-' && *(str + 1) != 0 && ft_isdigit(*(str + 1)))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return 0;
		i++;
	}
	return 1;
}

int 	check_args(int argc, char **argv, int isArgs)
{
	int i;
	int number;
	int count;

	i = (isArgs == 1) ? 1 : 0;
	while (i < argc)
	{
		if (!ft_isnumber(argv[i]))
			return 0;
		number = ft_atoi(argv[i]);
		count = (number < 0) ? ft_count_of_digits(number) + 1 : ft_count_of_digits(number);
		if (count != (int)ft_strlen(argv[i]) || (number == 0 && argv[i][0] != '0') || (number == -1 && argv[i][0] != '-'))
			return (0);
		i++;
	}
	return 1;
}

int 	check_duplicates(t_stack *a)
{
	t_elem *head;
	t_elem *cur;

	cur = a->head->next;
	while (cur != a->head)
	{
		if (cur->value == a->head->value)
			return 1;
		cur = cur->next;
	}
	head = a->head->next;
	while (head != a->head)
	{
		cur = a->head->next;
		while (cur != a->head)
		{
			if (cur != head && cur->value == head->value)
				return 1;
			cur = cur->next;
		}
		head = head->next;
	}
	return 0;
}

static int 	init_stacks_string(t_stack **a, t_stack **b, char *str)
{
	int i;
	char **split;

	i = count_words(str, ' ') - 1;
	split = ft_strsplit(str, ' ');
	if (!check_args(i + 1, split, 0))
	{
		free(*a);
		free(*b);
		return 1;
	}
	while (i >= 0)
	{
		add_front(*a, new_element(ft_atoi(split[i])));
		free(split[i]);
		i--;
	}
	free(split);
	return 0;
}

int		init_stacks(t_stack **a, t_stack **b, int argc, char **argv) /* todo: error_management with malloc and free memory */
{
	int i;

	if (argc == 1 || (argc != 2 && !check_args(argc, argv, 1)))
		return 1;
	if (!(*a = (t_stack *)malloc(sizeof(t_stack))))
		return 1;
	if (!(*b = (t_stack *)malloc(sizeof(t_stack))))
	{
		free(*a);
		return 1;
	}
	i = argc - 1;
	(*a)->size = 0;
	(*b)->size = 0;
	(*b)->head = NULL;
	if (argc == 2)
	{
		if (init_stacks_string(a, b, argv[1]))
			return 1;
	} else
		while (i > 0)
			add_front(*a, new_element(ft_atoi(argv[i--])));
	put_indexes(*a);
	return 0;
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