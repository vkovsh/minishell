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

#include "libft.h"

void	ft_bintree_infix_traverse(t_bintree **t,
		t_node_action action)
{
	if (*t == NULL)
		return ;
	ft_bintree_infix_traverse(&((*t)->left), action);
	action((*t)->key, (*t)->key_size,
			(*t)->value, (*t)->value_size);
	ft_bintree_infix_traverse(&((*t)->right), action);
}

void	ft_bintree_infix_traverse_reverse(t_bintree **t,
		t_node_action action)
{
	if (*t == NULL)
		return ;
	ft_bintree_infix_traverse_reverse(&((*t)->right), action);
	action((*t)->key, (*t)->key_size,
			(*t)->value, (*t)->value_size);
	ft_bintree_infix_traverse_reverse(&((*t)->left), action);
}
