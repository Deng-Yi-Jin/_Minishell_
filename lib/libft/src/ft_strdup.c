/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:06:17 by sinlee            #+#    #+#             */
/*   Updated: 2023/12/18 16:51:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// implementation of ft_strdup function

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, len + 1);
	return (ptr);
}

// test ft_strdup function
// #include <stdio.h>
// int main()
// {
// 	char *str;
// 	char *str2;

// 	str = strdup("Hello World!|");
// 	str2 = ft_strdup("Hello World!|");
// 	printf("%s\n", str);
// 	printf("%s\n", str2);
// 	return (0);
// }