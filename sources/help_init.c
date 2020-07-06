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

static int	check_args(int argc, char **argv, int is_args)
{
	int i;
	int number;
	int count;

	i = (is_args == 1) ? 1 : 0;
	while (i < argc)
	{
		if (!ft_isnumber(argv[i]))
			return (0);
		number = ft_atoi(argv[i]);
		count = (number < 0) ? ft_count_of_digits(number) + 1 :
				ft_count_of_digits(number);
		if (count != (int)ft_strlen(argv[i]) || (number == 0
		&& argv[i][0] != '0') || (number == -1 && argv[i][0] != '-'))
			return (0);
		i++;
	}
	return (1);
}

int			check_duplicates(t_stack *a)
{
	t_elem *head;
	t_elem *cur;

	cur = a->head->next;
	while (cur != a->head)
	{
		if (cur->value == a->head->value)
			return (1);
		cur = cur->next;
	}
	head = a->head->next;
	while (head != a->head)
	{
		cur = a->head->next;
		while (cur != a->head)
		{
			if (cur != head && cur->value == head->value)
				return (1);
			cur = cur->next;
		}
		head = head->next;
	}
	return (0);
}

static int	init_stacks_string(t_stack **a, t_stack **b, char *str)
{
	int		i;
	char	**split;

	i = count_words(str, ' ') - 1;
	split = ft_strsplit(str, ' ');
	if (!check_args(i + 1, split, 0))
	{
		free(*a);
		free(*b);
		while (i >= 0)
			free(split[i--]);
		free(split);
		return (1);
	}
	while (i >= 0)
	{
		add_front(*a, new_element(ft_atoi(split[i])));
		free(split[i]);
		i--;
	}
	free(split);
	return (0);
}

static int	is_one_arg(char *str)
{
	while (*str)
	{
		if (*str == ' ')
			return (1);
		str++;
	}
	return (0);
}

int			init_stacks(t_stack **a, t_stack **b, int argc, char **argv)
{
	int i;

	if (argc == 1 || (!is_one_arg(argv[1]) && !check_args(argc, argv, 1)))
		return (1);
	if (init_stack(a, b))
		return (1);
	i = argc - 1;
	if (argc == 2)
	{
		if (init_stacks_string(a, b, argv[1]))
			return (1);
	}
	else
		while (i > 0)
			add_front(*a, new_element(ft_atoi(argv[i--])));
	put_indexes(*a);
	return (0);
}
