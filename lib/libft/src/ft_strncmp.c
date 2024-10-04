/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:25:52 by sinlee            #+#    #+#             */
/*   Updated: 2024/10/04 15:15:44 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// implement of strncmp function

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && (*s1 || *s2))
	{
		if (*s1++ != *s2++)
			return (*(unsigned char *)--s1 - *(unsigned char *)--s2);
	}
	return (0);
}

// #include <stdio.h>

// int main(int argc, char **argv)
// {
// 	printf("%d\n", ft_strncmp(argv[1], argv[2], 5));
// 	printf("%d\n", strncmp(argv[1], argv[2], 5));
// }