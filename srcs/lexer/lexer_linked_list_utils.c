/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_linked_list_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:18:48 by djin              #+#    #+#             */
/*   Updated: 2024/09/25 23:22:10 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"

void	free_stack(t_token **tokens, void (*del)(void *), bool loop,
		char *input)
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
	int	i;

	i = 0;
	tokens = lst_first_last(tokens, false);
	while (tokens)
	{
		printf("#%i TOKEN : [%s]\n", i, tokens->cmd);
		printf("address : %p\n", tokens);
		printf("type : %d\n", tokens->type);
		tokens = tokens->next;
		i++;
	}
}
