/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:00:02 by geibo             #+#    #+#             */
/*   Updated: 2024/09/11 10:54:14 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotation(char *str)
{
	int		i;
	int		len;
	char	*output;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			len++;
		i++;
	}
	output = ft_calloc(len + 1, sizeof(char *));
	if (!output)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			i++;
		else
			output[len++] = str[i++];
	}
	output[len] = '\0';
	free(str);
	return (output);
}
