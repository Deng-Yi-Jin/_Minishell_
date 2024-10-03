/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:31:30 by geibo             #+#    #+#             */
/*   Updated: 2024/10/02 15:39:57 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_flag(char *s, char *split_q)
{
	static int	i;
	static char	*st_s;

	if (st_s != split_q)
	{
		st_s = split_q;
		i = 0;
	}
	if (*s == '\'')
	{
		i ^= 1;
	}
	return (i);
}

bool	check_pipe_and_heredoc(t_token *token, t_token **tokens, char *input)
{
	if (token->type == PIPE && token->next && token->next->type == PIPE)
	{
		print_error_and_free("syntax error near unexpected token `||'", tokens,
			input);
		return (true);
	}
	if (token->type == HERE_DOC && token->next && token->next->type == HERE_DOC)
	{
		print_error_and_free("syntax error near unexpected token", tokens,
			input);
		return (true);
	}
	return (false);
}

bool	check_redirection_tokens(t_token *token, t_token **tokens, char *input)
{
	if (token->type == REDIR_OUT_APPEND && token->next
		&& token->next->type == REDIR_OUT)
	{
		print_error_and_free("syntax error near unexpected token `>'", tokens,
			input);
		return (true);
	}
	if (token->type == REDIR_OUT_APPEND && token->next
		&& token->next->type == REDIR_OUT_APPEND)
	{
		print_error_and_free("syntax error near unexpected token `>>'", tokens,
			input);
		return (true);
	}
	return (false);
}

bool	check_consecutive_tokens(t_token *token, t_token **tokens, char *input)
{
	while (token)
	{
		if (check_pipe_and_heredoc(token, tokens, input))
			return (true);
		if (check_redirection_tokens(token, tokens, input))
			return (true);
		token = token->next;
	}
	return (false);
}
