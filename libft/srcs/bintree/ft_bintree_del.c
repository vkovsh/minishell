/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:00:50 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:00:52 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bintree_del(t_bintree **t,
		t_del *del_struct)
{
	if ((*t)->left)
		ft_bintree_del(&((*t)->left), del_struct);
	if ((*t)->right)
		ft_bintree_del(&((*t)->right), del_struct);
	ft_bintree_delone(t, del_struct);
}
