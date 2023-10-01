/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_separator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:27:44 by codespace         #+#    #+#             */
/*   Updated: 2023/09/11 13:57:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_symbol(char input)
{
	if (input == '|' || input == '|' || input == '<' || input == '>' || input == '(' || input == ')'
		|| input == '{' || input == '}' || input == '&' || input == '$' || input == '\'' || input == '\"'
		|| input == '@' || input == '!' || input == '#' || input == '%' || input == '^' || input == '*'
		|| input == '-' || input == '+' || input == '=' || input == '?' || input == '/' || input == ':'
		|| input == '.' || input == '[' || input == ']' || input == '_' || input == ',')
		return (true);
	else
		return (false);
}

void	is_symbol(char *input, int *i, t_token **tokens)
{
	int		count_words;

	count_words = 0;
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			count_words = 2;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 2), OR);
		}
		else
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), PIPE);
		}
	}
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (input[*i + 1] == '<' && input[*i] == '<')
		{
			count_words = 2;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 2), HERE_DOC);
		}
		else if (input[*i + 1] == '>' && input[*i] == '>')
		{
			count_words = 2;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 2), REDIR_OUT_APPEND);
		}
		else if (input[*i] == '>')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), REDIR_OUT);
		}
		else if (input[*i] == '<')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), REDIR_IN);
		}
	}
	if (input[*i] == '(' || input[*i] == ')' || input[*i] == '{' || input[*i] == '}')
	{
		if (input[*i] == '(')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), OPEN_BRACKET);
		}
		else if (input[*i] == ')')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), CLOSE_BRACKET);
		}
		else if (input[*i] == '{')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), OPEN_BRACE);
		}
		else if (input[*i] == '}')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), CLOSE_BRACE);
		}
	}
	if (input[*i] == '[' || input[*i] == ']')
	{
		if (input[*i] == '[')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), OPEN_SQUARE_BRACKET);
		}
		else if (input[*i] == ']')
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), CLOSE_SQUARE_BRACKET);
		}
	}
	if (input[*i] == '&')
	{
		if (input[*i + 1] == '&' && input[*i] == '&')
		{
			count_words = 2;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 2), DOUBLE_AND);
		}
		else
		{
			count_words = 1;
			(*tokens) = add_tokens(*tokens, ft_substr(input, *i, 1), ANDPARSEN);
		}
	}
	if (input[*i] == '$' || input[*i] == '\'' || input[*i] == '\"' || input[*i] == '!'
	|| input[*i] == '@' || input[*i] == '#' || input[*i] == '%' || input[*i] == '^'
	|| input[*i] == '*' || input[*i] == '-' || input[*i] == '_' || input[*i] == '+'
	|| input[*i] == '=' || input[*i] == '+' || input[*i] == ':' || input[*i] == '?'
	|| input[*i] == '.' || input[*i] == ',' || input[*i] == '/')
	{
		count_words = 1;
		(*tokens) = add_tokens(*tokens, ft_substr(input, *i, count_words), ft_checksymb(input[*i]));
	}
	*i += count_words;
}
