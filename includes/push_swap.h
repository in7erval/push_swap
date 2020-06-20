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
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"

# define RA	1
# define RB	2
# define RR  3
# define RRA 4
# define RRB 5
# define RRR 6
# define PA	7
# define PB	8
# define SA	9
# define SB	10
# define SS	11

# define WIDTH 500
# define HEIGHT 500
# define KEY_ESC 53
# define KEY_ENTER 36
# define KEY_A 0
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_DELETE 51

# define RED 0xff000
# define ORANGE 0xff4f00
# define YELLOW 0xf7ff00
# define GREEN 0x0bda51
# define LIGHT_BLUE 0x1e90ff
# define BLUE 0x0099EE
# define VIOLET 0x4d0092

# define DARK_VIOLET 0x1f1b24
# define BACKGROUND_SURFACE 0x121212
# define PRIMARY_VIOLET 0xbb86fc
# define DARK_BLUE 0x3700b3
# define DARK_TURQUOISE 0x03dac5

typedef struct			s_elem
{
	int					value;
	size_t				index;
	struct s_elem		*next;
	struct s_elem		*prev;
	int					keep;
	int					color;
}						t_elem;

typedef struct			s_stack
{
	t_elem				*head;
	size_t				size;
	t_elem				*markup;
}						t_stack;

typedef struct			s_opr
{
	size_t				operator_a;
	size_t				operator_b;
	size_t				count_a;
	size_t				count_b;
	t_elem				*elem;
}						t_opr;

typedef	struct			s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_list				*oprs;
	t_list				*cur;
	t_stack				*a;
	t_stack				*b;
	int					color_from;
	int					color_to;
	size_t				max_index;
	size_t				width;
	size_t				height;
}						t_mlx;

typedef	struct			s_point
{
	int					x;
	int					y;
	int					color;
}						t_point;

int						ft_abs(int i);
void					print_error(char *s);
void					add_front(t_stack *stack, t_elem *elem);
void					add_back(t_stack *stack, t_elem *elem);
t_elem					*new_element(int value);
int						init_stacks(t_stack **a, t_stack **b,
						int argc, char **argv);
void					push(t_stack *from, t_stack *to,
						t_list **oprs, char *str);
t_elem					*pop(t_stack *b);
void					swap(t_stack *stack, t_list **oprs, char *str);
void					print_stack(t_stack *b);
void					reverse_rotate(t_stack *buf, t_list **oprs, char *str);
void					rotate(t_stack *buf, t_list **oprs, char *str);
void					print_stacks(t_stack *a, t_stack *b);
int						find_max(t_elem *a, t_elem *b);
void					free_stack(t_stack **stack);
void					free_list(t_list **list);
int						ft_isnumber(char *str);
void					print_space(int a, int max);
void					print_line(int a, char c);
int						count_words(const char *str, char c);
t_list					*solve(t_stack *a, t_stack *b,
						int (*markup)(t_stack *, t_elem *));
void					do_opr(t_opr o, t_stack *a, t_stack *b, t_list **oprs);
t_opr					count_opr_b(t_stack *a, t_stack *b);
t_opr					count_opr_a(t_stack *a, t_elem *elem);
int						count_closest(t_stack *a, t_elem *elem);
int						count_keep(t_stack *stack);
int						contains_not_keep(t_elem *head);
int						try_to_sa(t_stack *a,
						int (*markup)(t_stack *, t_elem *));
t_stack					*clone_stack(t_stack *a);
t_elem					*create_elem(int value, int index, int keep);
void					put_indexes(t_stack *a);
void					print_operations(t_list *oprs);
int						markup_all(t_stack *a,
						int (*markup)(t_stack *, t_elem *));
int						greater(t_stack *a, t_elem *markup_head);
int						by_index(t_stack *a, t_elem *markup_head);
void					ft_lstaddnew(t_list **list, char *str);
size_t					count_nodes(t_list *oprs);
int						check_duplicates(t_stack *a);
void					put_pixel(t_mlx *m, t_point p);
void					put_rectangle(t_mlx *m, t_point p,
						int width, int height);
t_point					new_point(int x, int y, int color);
void					drawing(t_stack *a, t_stack *b, t_list *oprs);
int						check(t_stack *a, t_stack *b);
int						exit_program(void *param);
void					draw_stack(t_mlx *m, t_stack *stack, int x, int height);
void					do_operation(t_mlx *m);
void					draw_stacks(t_mlx *m);
t_mlx					*drawing_init(t_stack *a, t_stack *b, t_list *oprs);
int						deal_key(int keycode, t_mlx *mlx);
void					mlx_hooks(t_mlx *m);
int						get_color(int color1, int color2, float percent);
void					put_colors(t_mlx *m);
int						get_light(int start, int end, float percentage);
size_t					find_max_index(t_stack *a);
int						check_all(char *str, t_stack *a, t_stack *b);
void					double_swap(t_stack *a, t_stack *b);
void					double_rotate(t_stack *a, t_stack *b);
void					double_reverse_rotate(t_stack *a, t_stack *b);
int						check(t_stack *a, t_stack *b);
#endif
