/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:49:19 by djin              #+#    #+#             */
/*   Updated: 2024/02/06 05:52:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *cmd, int type)
{
	t_token	*newnode;

	newnode = malloc(sizeof(t_token));
	if (newnode == NULL)
		return (NULL);
	newnode -> cmd = cmd;
	newnode -> type = type;
	newnode -> next = NULL;
	newnode -> prev = NULL;
	return (newnode);
}

// creates a new token
t_token	*add_tokens(t_token *tokens, char *input, int type)
{
	t_token	*new;

	new = create_token(input, type);
	if (!new)
		return (NULL);
	if (!(tokens))
		return (new);
	tokens -> next = new;
	new -> prev = tokens;
	return (new);
}

t_token	*add_null_token(t_token *tokens)
{
	t_token	*new;

	new = create_token(NULL, NULL);
	if (!new)
		return (NULL);
	if (!(tokens))
		return (new);
	tokens -> next = new;
	new->prev = tokens;
	return (new);
}

t_token	*lst_first_last(t_token *tokens, bool is_last)
{
	if (is_last == true)
	{
		while (tokens -> next != NULL && tokens != NULL)
			tokens = tokens -> next;
		return (tokens);
	}
	while (tokens -> prev != NULL && tokens != NULL)
		tokens = tokens -> prev;
	return (tokens);
}

t_token	*lst_go_back(t_token *tokens)
{
	while ((tokens)->prev != NULL && (tokens)->prev->type != PIPE)
		tokens = tokens->prev;
	return (tokens);
}
