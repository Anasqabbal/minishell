/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:40:04 by anqabbal          #+#    #+#             */
/*   Updated: 2023/12/16 10:12:36 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (((int)count < 0 && (int)size < 0))
		return (0);
	arr = malloc(size * count);
	if (!arr)
		return (0);
	ft_bzero(arr, count * size);
	return (arr);
}
