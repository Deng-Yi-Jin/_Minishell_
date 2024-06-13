/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_separator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:27:44 by codespace         #+#    #+#             */
/*   Updated: 2024/06/13 15:00:10 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_symbol(char input)
{
	if (input == '>' || input == '<' || input == '|' || input == ' ')
		return (true);
	return (false);
}

bool	ft_bracket(char input)
{
	if (input == '(' || input == ')' || input == '{' || input == '}')
		return (true);
	return (false);
}

void	ft_redir(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>' && input[(*i) + 1] == '>')
	{
		(*tokens) = add_tokens((*tokens), ft_substr(input, *i, 2), REDIR_OUT_APPEND);
		*i += 2;
	}
	else if (input[*i] == '<' && input[(*i) + 1] == '<')
	{
		(*tokens) = add_tokens((*tokens), ft_substr(input, *i, 2), HERE_DOC);
		*i += 2;
	}
	else
	{
		(*tokens) = add_tokens((*tokens), ft_substr(input, *i, 1), ft_return_op(input[*i]));
		(*i)++;
	}
}

void	ft_pipe(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		(*tokens) = add_tokens((*tokens), ft_substr(input, *i, 1), PIPE);
		(*i)++;
	}
}

int ft_return_op(char input)
{
	if (input == '>')
		return (REDIR_OUT);
	else if (input == '<')
		return (REDIR_IN);
	else if (input == '|')
		return (PIPE);
	else if (input == ' ')
		return (SPACE);
	return (0);
}
