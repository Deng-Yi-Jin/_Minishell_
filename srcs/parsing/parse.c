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
	t_ast	**new_ast;

	(*tokens) = lst_first_last(*tokens, false);
	ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = NULL;
	while ((*tokens)->cmd != NULL)
	{
		while ((*tokens)->type != PIPE || (*tokens)->type != OR)
		{
			if (((*tokens)->prev == NULL || (*tokens)->prev->type == PIPE)
			|| (*tokens)->next != NULL || (*tokens)->next->type != PIPE)
			{
				(*ast) = add_child(*ast, (*tokens)->cmd);
				(*ast) = (*ast)->next_grandchild;
				(*tokens) = (*tokens)->next;
			}
			else if ((*tokens)->next == NULL || (*tokens)->next->type == PIPE)
			{
				(*ast) = add_last_child(*ast, (*tokens)->cmd);
				(*ast)->next = add_db_node(*ast);
				(*ast) = (*ast)->next;
				(*tokens) = (*tokens)->next;
			}
		}
		if ((*tokens)->type == PIPE || (*tokens)->type == OR)
			(*tokens) = (*tokens)->next;
	}
	// printf("%s\n", (*ast)->cmd);
	// printf("%p\n", (*tokens));
	// *ast = NULL;
	print_ast_all(ast);
	free_ast(ast);
	free(ast);
}

