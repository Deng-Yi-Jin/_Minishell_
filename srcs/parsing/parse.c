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
	ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = NULL;
	(*ast) = create_ast_node(NULL);
	while ((*tokens)->cmd != NULL)
	{
		if ((*tokens)->prev == NULL && (*tokens)->type != PIPE)
		{
			(*ast)->next_child = create_ast_node(ft_strdup((*tokens)->cmd));
			(*ast)->next_child->parent = (*ast);
			(*ast) = (*ast)->next_child;
		}
		else if ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
		{
			(*ast)->next_grandchild = create_ast_node(ft_strdup((*tokens)->cmd));
			(*ast)->next_grandchild->prev_grandchild = (*ast);
			(*ast) = (*ast)->next_grandchild;
		}
		else if ((*tokens)->type == PIPE)
		{
			(*tokens) = (*tokens)->next;
			(*ast) = ast_first_last((*ast), true, false);
			(*ast)->next_child = create_ast_node(ft_strdup((*tokens)->cmd));
			(*ast)->next_child->parent = (*ast)->parent;
			(*ast)->next_child->prev_child = (*ast);
			(*ast) = (*ast)->next_child;
		}
		(*tokens) = (*tokens)->next;
	}
	(*ast) = ast_first_last(*ast, true, true);
	print_ast_all(ast);
	free_ast(ast);
	free(ast);
}

