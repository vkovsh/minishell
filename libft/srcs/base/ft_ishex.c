/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 11:51:11 by vkovsh            #+#    #+#             */
/*   Updated: 2018/01/03 11:53:22 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ishex(char c)
{
	if (ft_isdigit(c) || (c >= 'a' && c <= 'f') ||
			(c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}
