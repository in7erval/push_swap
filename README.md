# Push_swap
---
# What is it?
The Push_swap project is a very simple and highly effective algorithm project: data will need to be sorted. You have at your disposal a set of int values, 2 stacks and a set of instructions to manipulate both stacks.
> Operations:
- *sa* : swap a - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements).
- *sb* : swap b - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements).
- *ss* : sa and sb at the same time.
- *pa* : push a - take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
- *pb* : push b - take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
- *ra* : rotate a - shift up all elements of stack a by 1. The first element becomes the last one.
- *rb* : rotate b - shift up all elements of stack b by 1. The first element becomes the last one.
- *rr* : ra and rb at the same time.
- *rra* : reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one.
- *rrb* : reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one.
- *rrr* : rra and rrb at the same time.
---
## Installation
- Just do ```make``` :)
---
## Usage
```shell
$ ARG=`./gen.sh 50`;./push_swap $ARG
```

```./gen.sh 50``` is a Ruby program, that create random 50 values (from 1 to 50)


---
## Visual
### Installation
```shell
make visual
```
### Usage
```shell
$ ARG=`./gen.sh 100`;./push_swap $ARG | ./checker_visual $ARG
```

![push_swap](https://github.com/in7erval/push_swap/blob/master/gif_pw.gif)
