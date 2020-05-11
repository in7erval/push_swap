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

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include "libft.h"
#include "ft_printf.h"

#define RA	1
#define RB	2
#define RR  3
#define RRA 4
#define RRB 5
#define RRR 6
#define PA	7
#define PB	8
#define SA	9
#define SB	10
#define SS	11

typedef struct			s_elem
{
	int					value;
	size_t 				index;
	struct s_elem		*next;
	struct s_elem		*prev;
	int 				keep;
}						t_elem;

typedef struct	s_stack
{
	t_elem 		*head;
	size_t 		size;
	t_elem		*markup;
}				t_stack;

typedef struct	s_opr
{
	size_t 		operator_a;
	size_t 		operator_b;
	size_t 		count_a;
	size_t 		count_b;
	t_elem 		*elem;
}				t_opr;



int 	ft_abs(int i);
void 	print_error(char *s);
void	add_front(t_stack *stack, t_elem *elem);
void	add_back(t_stack *stack, int elem);
void	init_stacks(t_stack **a, t_stack **b, int argc, char **argv);
void	push(t_stack *from, t_stack *to, t_list **oprs, char *str);
t_elem	*pop(t_stack *b);
void	swap(t_stack *stack, t_list **oprs, char *str);
void	print_stack(t_stack *b);
void	reverse_rotate(t_stack *buf, t_list **oprs, char *str);
void	rotate(t_stack *buf, t_list **oprs, char *str);
void	print_stacks(t_stack *a, t_stack *b);
int		find_max(t_elem *a, t_elem *b);
void	free_stacks(t_stack **a, t_stack **b);
void	free_list(t_list **list);

void	print_space(int a, int max);
void	print_line(int a, char c);
int		count_words(const char *str, char c);

t_list	*solve(t_stack *a, t_stack *b, int (*markup)(t_stack *, t_elem *));
void	put_indexes(t_stack *a);
void	add_n_operations(t_list *oprs, int n, char *str);
void	print_stack_debug(t_stack *stack);
void	sort_array(int *array, int size);
void	print_operations(t_list *oprs);
int		markup_all(t_stack *a, int (*markup)(t_stack *, t_elem *));
int		greater(t_stack *a, t_elem *markup_head);
int 	by_index(t_stack *a, t_elem *markup_head);
void	ft_lstaddnew(t_list **list, char *str);
size_t	count_nodes(t_list *oprs);
#endif
