/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kshim <kshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:15:42 by kshim             #+#    #+#             */
/*   Updated: 2022/03/24 08:54:52 by kshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	if (len == 0)
		return (dst);
	if (str1 > str2)
	{
		i = len;
		while (i-- > 0)
		{
			str1[i] = str2[i];
		}
	}
	else if (str1 < str2)
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
