/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_delone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:02:00 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:02:02 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bintree_delone(t_bintree **t,
		t_del *del_struct)
{
	del_struct->del_node(&((*t)->node), del_struct->del_k, del_struct->del_v);
	free(*t);
	*t = NULL;
}
