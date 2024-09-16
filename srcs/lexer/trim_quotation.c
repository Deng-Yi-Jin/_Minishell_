/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:00:02 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 16:24:55 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_non_quote_chars(const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

char	*allocate_output_string(int len)
{
	char	*output;

	output = ft_calloc(len + 1, sizeof(char));
	if (!output)
		return (NULL);
	return (output);
}

void	copy_non_quote_chars(char *output, const char *str)
{
	int	i;
	int	len;

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
}

char	*trim_quotation(char *str)
{
	int		len;
	char	*output;

	len = count_non_quote_chars(str);
	output = allocate_output_string(len);
	if (!output)
		return (NULL);
	copy_non_quote_chars(output, str);
	free(str);
	return (output);
}
