/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_linked_list_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:18:48 by djin              #+#    #+#             */
/*   Updated: 2024/09/09 18:13:43 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

void	free_stack(t_token **tokens, void (*del)(void *),
			bool loop, char *input)
{
	t_token	*tmp;

	if (!(tokens) || !(*tokens))
		return ;
	(*tokens) = lst_first_last((*tokens), false);
	if (!loop)
	{
		tmp = (*tokens)->next;
		free((*tokens)->cmd);
		free(*tokens);
		(*tokens) = tmp;
	}
	else
	{
		while (*tokens)
		{
			tmp = (*tokens)->next;
			free((*tokens)->cmd);
			free(*tokens);
			(*tokens) = tmp;
		}
	}
}

void	print_stack(t_token *tokens)
{
	int i = 0;
	tokens = lst_first_last(tokens, false);
	while (tokens)
	{
		printf("#%i TOKEN : [%s]\n", i, tokens->cmd);
		printf("address : %p\n", tokens);
		printf("type : %d\n\n", tokens->type);
		tokens = tokens->next;
		i++;
	}
}
