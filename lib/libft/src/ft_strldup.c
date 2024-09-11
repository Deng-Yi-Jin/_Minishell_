/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:42:48 by kytan             #+#    #+#             */
/*   Updated: 2024/09/11 09:44:51 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(char *src, ptrdiff_t size)
{
	char	*dup;
	int		i;

	i = 0;
	if (size <= 0 || !src)
		return (0);
	dup = malloc(size * sizeof(char));
	if (!dup)
		return (0);
	while (*src && i + 1 < size)
		dup[i++] = *src++;
	if (i < size)
		dup[i] = '\0';
	return (dup);
}