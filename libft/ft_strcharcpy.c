/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcharcpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 11:42:54 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 17:22:58 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcharcpy(char *dest, const char *src, size_t n, char c)
{
	size_t		i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = c;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
