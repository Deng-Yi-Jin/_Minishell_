/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:25:52 by sinlee            #+#    #+#             */
/*   Updated: 2024/06/13 19:49:32 by geibo            ###   ########.fr       */
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