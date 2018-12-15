/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_numeric_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:53:59 by vkovsh            #+#    #+#             */
/*   Updated: 2018/03/16 14:55:56 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	is_numeric_type(t_type t)
{
	if (t == i || t == d || t == u ||
			t == U || t == o || t == O ||
			t == x || t == X || t == b || t == B)
		return (TRUE);
	return (FALSE);
}
