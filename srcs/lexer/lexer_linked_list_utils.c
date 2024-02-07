/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_linked_list_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:18:48 by djin              #+#    #+#             */
/*   Updated: 2024/02/06 05:54:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_stack(t_token **tokens, void (*del)(void *), bool loop)
{
	t_token	*tmp;

	if (!(tokens) || !(*tokens))
		return ;
	(*tokens) = lst_first_last((*tokens), false);
	if (!loop)
	{
		tmp = (*tokens) -> next;
		free((*tokens)->cmd);
		free(*tokens);
		(*tokens) = tmp;
	}
	else
	{
		while (*tokens)
		{
			tmp = (*tokens) -> next;
			free((*tokens)->cmd);
			free(*tokens);
			(*tokens) = tmp;
		}
	}
}

void	print_stack(t_token *tokens)
{
	tokens = lst_first_last(tokens, false);
	while (tokens)
	{
		if (tokens != NULL)
		{
			printf("stack_a: %s\n", tokens->cmd);
			printf("stack_a address: %p\n", tokens);
			printf("stack_a type: %d\n", tokens->type);
			tokens = tokens->next;
		}
	}
}
