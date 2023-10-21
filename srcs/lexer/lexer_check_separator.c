/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_separator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:27:44 by codespace         #+#    #+#             */
/*   Updated: 2023/10/19 10:57:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_symbol(char input)
{
	if (input == '>' || input == '<' || input == '|' || input == ' ')
		return (true);
	return (false);
}

void	ft_redir(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>' && input[(*i) + 1] == '>')
	{
		(*tokens) = add_tokens((*tokens), ft_substr(input, *i, 2), REDIR_OUT);
		*i += 2;
	}
	else if (input[*i] == '<' && input[(*i) + 1] == '<')
	{
		(*tokens) = add_tokens((*tokens), ft_substr(input, *i, 2), REDIR_IN);
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
	if (input[*i] == '|' && input[(*i) + 1] == '|')
	{
		(*tokens) = add_tokens((*tokens), ft_substr(input, *i, 2), OR);
		*i += 2;
	}
	else
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