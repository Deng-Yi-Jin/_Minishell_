/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:55:38 by root              #+#    #+#             */
/*   Updated: 2023/10/01 16:52:194 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_token **tokens)
{
	t_ast	**ast;
	(*tokens) = lst_first_last(*tokens, false);
	ast = malloc(sizeof(t_ast *));
	*ast = NULL;
	while ((*tokens)->cmd != NULL)
	{
		while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
		{
			if ((*tokens)->type == DOLLAR && (*tokens)->next->type == WORD)
			{
				*ast = add_ast(*ast, ft_strjoin((*tokens)->cmd, (*tokens)->next->cmd));
				(*tokens) = (*tokens)->next->next;
			}
			else if((*tokens)->type == WORD)
			{
				*ast = add_ast(*ast, ft_strdup((*tokens)->cmd));
				(*tokens) = (*tokens)->next;
			}
			else if((*tokens)->type == MINUS && (*tokens)->next->type == WORD)
			{
				*ast = add_ast(*ast, ft_strjoin((*tokens)->cmd, (*tokens)->next->cmd));
				(*tokens) = (*tokens)->next->next;
			}
			else
			{
				*ast = add_ast(*ast, ft_strdup((*tokens)->cmd));
				(*tokens) = (*tokens)->next;
			}
		}
		if ((*tokens)->type == PIPE)
		{
			(*tokens) = (*tokens)->next;
			
		}
	}
	*ast = ast_first_last(*ast, false);
	// printf("%s\n", (*ast)->cmd);
	// printf("%p\n", (*tokens));
	// *ast = NULL;
	print_ast_all(ast);
	free_ast(ast);
	free(ast);
}

