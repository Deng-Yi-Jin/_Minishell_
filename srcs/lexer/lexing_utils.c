/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:05:51 by root              #+#    #+#             */
/*   Updated: 2024/09/29 22:00:42 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotation(char *input, int *i, int *count_words, char c)
{
	while (ft_symbol(input[*i]) == false && input[*i])
	{
		(*i)++;
		(*count_words)++;
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
		(*tokens) = add_tokens((*tokens), ft_substr(input, j, (*count_words)
					+ 1), DOLLAR);
	}
	if (ft_symbol(input[*i]) == false && input[*i])
	{
		j = *i;
		quotation(input, i, count_words, input[*i]);
		(*tokens) = add_tokens((*tokens), ft_substr(input, j, *count_words),
				CMD);
	}
	if (input[*i] == '>' || input[*i] == '<')
		ft_redir(input, i, tokens);
	else if (input[*i] == '|')
		ft_pipe(input, i, tokens);
}
