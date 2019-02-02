/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:05:32 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:05:34 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bintree		*ft_right_rotate(t_bintree *p)
{
	t_bintree	*q;

	q = p->left;
	p->left = q->right;
	q->right = p;
	ft_fixheight(p);
	ft_fixheight(q);
	return (q);
}

t_bintree		*ft_left_rotate(t_bintree *q)
{
	t_bintree	*p;

	p = q->right;
	q->right = p->left;
	p->left = q;
	ft_fixheight(q);
	ft_fixheight(p);
	return (p);
}
