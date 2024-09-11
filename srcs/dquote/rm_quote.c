/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:47:02 by geibo             #+#    #+#             */
/*   Updated: 2024/09/09 18:32:26 by kytan            ###   ########.fr       */
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

char	*rm_quote(char *str)
{
	char	*new_str;
	int		quotes;

	if (!str[0] || !str)
		return (str);
	quotes = quote_or_dquote(str);
	if (quotes == SINGLE_QUOTE)
		new_str = unquote_str(str, '\'');
	else if (quotes == DOUBLE_QUOTE)
		new_str = unquote_str(str, '\"');
	else
		new_str = unquote_str(str, '\0');
	return (new_str);
}

/* KYLIE TINKERED WITH 5:31PM 8/14/2024

split rm_quote(): added handle_quote()
added macros

*/
/*
int	quote_or_dquote(char *str)
{
	int		i;
	// bool	quote;
	// bool	dquote;

	i = 0;
	// quote = false;
	// dquote = false;
	while (str[i])
	{
		if (str[i] == '\'' && !dquote)
			return (SINGLE_QUOTE);
		// {
		// 	quote = true;
		// 	break ;
		// }
		else if (str[i] == '\"' && !quote)
			return (DOUBLE_QUOTE);
		// {
		// 	dquote = true;
		// 	break ;
		// }
		i++;
	}
	// if (quote)
	// 	return (1);
	// else if (dquote)
	// 	return (2);
	return (NO_QUOTE);
}*/
/*char	*rm_quote(char *str)
{
	char	*new_str;
	int		quotes;
	// int		i;
	// int		j;

	if (!str[0] || !str)
		return (str);
	// new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	quotes = quote_or_dquote(str);
	// i = 0;
	// j = 0;
	if (quotes == SINGLE_QUOTE)
		new_str = handle_quote(str, '\'');
	// {
	// 	while (str[i])
	// 	{
	// 		if (str[i] == '\'')
	// 			i++;
	// 		if (str[i])
	// 			new_str[j++] = str[i++];
	// 	}
	// }
	else if (quotes == DOUBLE_QUOTE)
		new_str = handle_quote(str, '\"');
	// {
	// 	while (str[i])
	// 	{
	// 		if (str[i] == '\"')
	// 			i++;
	// 		if (str[i])
	// 			new_str[j++] = str[i++];
	// 	}
	// }
	else
		new_str = handle_quote(str, '\0');
		// while (str[i])
		// 	new_str[j++] = str[i++];
	// new_str[j] = '\0';
	return (new_str);
}*/