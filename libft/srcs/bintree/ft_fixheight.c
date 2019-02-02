/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fixheight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:04:29 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:04:32 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_fixheight(t_bintree *t)
{
	unsigned char	hl;
	unsigned char	hr;

	hl = HEIGHT(t->left);
	hr = HEIGHT(t->right);
	t->height = ((hl > hr) ? hl : hr) + 1;
}
