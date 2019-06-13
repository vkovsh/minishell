/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_postfix_traverse.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:01:10 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:01:12 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bintree_postfix_traverse(t_bintree **t,
		t_node_action action)
{
	if (*t == NULL)
		return ;
	ft_bintree_postfix_traverse(&((*t)->left), action);
	ft_bintree_postfix_traverse(&((*t)->right), action);
	action(&((*t)->node));
}
