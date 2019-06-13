/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bintree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:12:50 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:12:51 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINTREE_H
# define BINTREE_H
# include <sys/types.h>
# include <stdlib.h>
# define HEIGHT(n)((n)?n->height:0)
# define BFACTOR(n)(HEIGHT(n->right)-HEIGHT(n->left))

typedef struct			s_node
{
	void				*key;
	size_t				key_size;
	void				*value;
	size_t				value_size;
}						t_node;

typedef struct			s_bintree
{
	unsigned char		height;
	struct s_node		node;
	struct s_bintree	*left;
	struct s_bintree	*right;
}						t_bintree;

typedef int		(*t_compare_keys)(const void *k1, const void *k2, size_t key_size);

typedef void	(*t_node_action)(t_node *node);

typedef void	(*t_del_node)(t_node *node);

void					ft_fixheight(t_bintree *t);

t_bintree				*ft_right_rotate(t_bintree *t);

t_bintree				*ft_left_rotate(t_bintree *t);

t_bintree				*ft_balance(t_bintree *p);

void					ft_bintree_add(t_bintree **t,
	t_bintree *node, t_compare_keys compare);

t_bintree				*ft_bintree_new(const t_node *item);

t_bintree				*ft_bintree_find(t_bintree **t,
							const void *key,
							const size_t key_size,
							t_compare_keys compare);

void					ft_bintree_delone(t_bintree **t,
							t_del_node del);

void					ft_bintree_del(t_bintree **t,
							t_del_node del);

void					ft_bintree_infix_traverse(t_bintree **t,
							t_node_action action);

void					ft_bintree_prefix_traverse(t_bintree **t,
							t_node_action action);

void					ft_bintree_postfix_traverse(t_bintree **t,
							t_node_action action);

void					ft_bintree_infix_traverse_reverse(t_bintree **t,
							t_node_action action);

/*
** Arguments:	t_bintree **t - adress of tree main node
**				void *key - key value of target node
**				size_t key_size - size of key value
**				t_compare_keys cmp - function for key compare
** Return:		1 if node with  key exists, 0 otherwise
*/
t_bintree				*ft_bintree_remove(t_bintree *t,
							const void *key,
							const size_t key_size,
							t_compare_keys cmp,
							t_del_node del);
#endif
