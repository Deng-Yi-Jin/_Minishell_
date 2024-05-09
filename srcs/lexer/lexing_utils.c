/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:05:51 by root              #+#    #+#             */
/*   Updated: 2024/05/08 14:36:27 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotation(char *input, int *i, int *count_words, char c)
{
	if (input[*i] == '\'')
		quoting(input, i, count_words, '\'');
	else if (input[*i] == '\"')
		quoting(input, i, count_words, '\"');
	else if (input[*i] == '`')
		quoting(input, i, count_words, '`');
	else
	{
		while (ft_symbol(input[*i]) == false && input[*i])
		{
			(*i)++;
			(*count_words)++;
		}
	}
}

void	start_lex(char *input, t_token **tokens)
{
	int	i;
	int	count_words;

	i = 0;
	count_words = 0;
	while (input[i])
	{
		count_words = 0;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		lexing(input, tokens, &i, &count_words);
	}
	(*tokens) = add_null_token(*tokens);
	(*tokens) = lst_go_back(*tokens);
}

void	lexing(char *input, t_token **tokens, int *i, int *count_words)
{
	int	j;

	if (input[*i] == '$')
	{
		j = *i;
		dollar(input, i, count_words);
		(*tokens) = \
		add_tokens((*tokens), ft_substr(input, j, (*count_words) + 1), DOLLAR);
	}
	if (ft_symbol(input[*i]) == false && input[*i])
	{
		j = *i;
		if (ft_symbol(input[*i]) == false && input[*i])
			quotation(input, i, count_words, input[*i]);
		(*tokens) = \
		add_tokens((*tokens), ft_substr(input, j, *count_words), CMD);
	}
	if (input[*i] == '>' || input[*i] == '<')
		ft_redir(input, i, tokens);
	else if (input[*i] == '|')
		ft_pipe(input, i, tokens);
}
