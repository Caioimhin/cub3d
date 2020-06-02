/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:05:42 by kparis            #+#    #+#             */
/*   Updated: 2020/05/13 19:02:50 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t			i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	i = 0;
	ptr_dest = dest;
	ptr_src = (unsigned char *)src;
	if (dest == (char *)src)
		return (dest);
	while (i != size)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}
