/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:47:02 by geibo             #+#    #+#             */
/*   Updated: 2024/10/01 08:14:31 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NO_QUOTE 0
#define SINGLE_QUOTE 1
#define DOUBLE_QUOTE 2

int	quote_or_dquote(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			return (SINGLE_QUOTE);
		else if (str[i] == '\"')
			return (DOUBLE_QUOTE);
	}
	return (NO_QUOTE);
}

char	*unquote_str(char *str, char c)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (c != '\0' && str[i] == c)
			i++;
		if (str[i])
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*unquote_squote(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'')
			i++;
		if (str[i])
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*rm_quote(char *str)
{
	char	*new_str;
	int		quotes;

	if (!str[0] || !str)
		return (str);
	quotes = quote_or_dquote(str);
	if (quotes == DOUBLE_QUOTE)
		new_str = unquote_str(str, '\"');
	else
		new_str = unquote_str(str, '\0');
	return (new_str);
}
