/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:00:58 by kytan             #+#    #+#             */
/*   Updated: 2024/09/15 17:59:22 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s, const char *c)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s;
	b = (unsigned char *)c;
	if (!s || !c)
		return (-1);
	while (*a == *b && *a)
	{
		++a;
		++b;
	}
	return (*a - *b);
}