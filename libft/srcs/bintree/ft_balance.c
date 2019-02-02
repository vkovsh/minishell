/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_balance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 14:59:54 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 14:59:56 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bintree		*ft_balance(t_bintree *p)
{
	ft_fixheight(p);
	if (BFACTOR(p) == 2)
	{
		if (BFACTOR(p->right) < 0)
			p->right = ft_right_rotate(p->right);
		return (ft_left_rotate(p));
	}
	if (BFACTOR(p) == -2)
	{
		if (BFACTOR(p->left) > 0)
			p->left = ft_left_rotate(p->left);
		return (ft_right_rotate(p));
	}
	return (p);
}
