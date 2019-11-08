/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_infix_traverse.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:03:05 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:03:07 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bintree.h"

void	ft_bintree_infix_traverse(t_bintree **t,
		t_node_action action,
		void *out)
{
	if (*t == NULL)
		return ;
	ft_bintree_infix_traverse(&((*t)->left), action, out);
	action(&((*t)->node), out);
	ft_bintree_infix_traverse(&((*t)->right), action, out);
}

void	ft_bintree_infix_traverse_reverse(t_bintree **t,
		t_node_action action,
		void *out)
{
	if (*t == NULL)
		return ;
	ft_bintree_infix_traverse_reverse(&((*t)->right), action, out);
	action(&((*t)->node), out);
	ft_bintree_infix_traverse_reverse(&((*t)->left), action, out);
}
