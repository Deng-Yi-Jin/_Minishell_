/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:27:25 by geibo             #+#    #+#             */
/*   Updated: 2024/09/30 09:47:13 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	free(content);
}

void	print_error_and_free(const char *error_message, t_token **tokens,
		char *input)
{
	printf("%s\n", error_message);
	free_stack(tokens, del, true, input);
	free(tokens);
}

bool	check_first_token(t_token *token, t_token **tokens, char *input)
{
	if (token->type == PIPE)
	{
		print_error_and_free("syntax error near unexpected token `|'", tokens,
			input);
		return (true);
	}
	if (token->type == DOLLAR)
	{
		print_error_and_free("syntax error near unexpected token `$'", tokens,
			input);
		return (true);
	}
	return (false);
}

void	print_tokens(t_token **tokens)
{
	t_token	*token;

	token = lst_first_last(*tokens, false);
	while (token)
	{
		printf("TOKEN %p\n", token);
		printf("cmd = \t[%s]\n", token->cmd);
		printf("type = \t[%i]\n", token->type);
		printf("prev = \t[%p]\n", token->prev);
		printf("next = \t[%p]\n\n", token->next);
		token = token->next;
	}
}

bool	check_consecutive_tokens(t_token *token, t_token **tokens, char *input)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
		{
			print_error_and_free("syntax error near unexpected token `||'",
				tokens, input);
			return (true);
		}
		if (token->type == HERE_DOC && token->next
			&& token->next->type == HERE_DOC)
		{
			print_error_and_free("syntax error near unexpected token", tokens,
				input);
			return (true);
		}
		if (token->type == HERE_DOC && token->next
			&& token->next->type == HERE_DOC)
		{
			print_error_and_free("syntax error near unexpected token", tokens,
				input);
			return (true);
		}
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
		token = token->next;
	}
	return (false);
}

bool	check_last_token(t_token *token, t_token **tokens, char *input)
{
	while (token->next && token->next->type != 0)
		token = token->next;
	if (token->type == PIPE || token->type == 0)
	{
		print_error_and_free("syntax error near unexpected token `|'", tokens,
			input);
		return (true);
	}
	else if (token->type == OR)
	{
		print_error_and_free("syntax error near unexpected token `||'", tokens,
			input);
		return (true);
	}
	else if (token->type == HERE_DOC || token->type == REDIR_OUT || token->type == REDIR_OUT_APPEND)
	{
		print_error_and_free("syntax error near unexpected token `newline'", tokens,
			input);
		return (true);
	}
	return (false);
}
