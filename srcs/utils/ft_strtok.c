/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:58:32 by sinlee            #+#    #+#             */
/*   Updated: 2023/08/17 08:08:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// done, any question?
char	*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	int			i;
	int			j;

	if (str != NULL)
		s = str;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (delim[j])
		{
			if (s[i] == delim[j])
			{
				s[i] = '\0';
				s = &s[i + 1];
				return (s);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
