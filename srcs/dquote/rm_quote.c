/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:47:02 by geibo             #+#    #+#             */
/*   Updated: 2024/08/01 17:16:59 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_or_dquote(char *str)
{
	int		i;
	bool	quote;
	bool	dquote;

	i = 0;
	quote = false;
	dquote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !dquote)
		{
			quote = true;
			break ;
		}
		else if (str[i] == '\"' && !quote)
		{
			dquote = true;
			break ;
		}
		i++;
	}
	if (quote)
		return (1);
	else if (dquote)
		return (2);
	return (0);
}

char	*rm_quote(char *str)
{
	char	*new_str;
	int		quotes;
	int		i;
	int		j;

	i = 0;
	if (!str[i] || !str)
		return (str);
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	quotes = quote_or_dquote(str);
	i = 0;
	j = 0;
	if (quotes == 1 && str)
	{
		while (str[i])
		{
			if (str[i] == '\'')
				i++;
			if (str[i])
			{
				new_str[j] = str[i];
				i++;
				j++;
			}
		}
	}
	else if (quotes == 2 && str)
	{
		while (str[i])
		{
			if (str[i] == '\"')
				i++;
			if (str[i])
			{
				new_str[j] = str[i];
				i++;
				j++;
			}
		}
	}
	else
	{
		while (str[i])
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}
