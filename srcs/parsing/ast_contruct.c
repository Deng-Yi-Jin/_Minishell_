/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_contruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:22:26 by djin              #+#    #+#             */
/*   Updated: 2024/02/06 07:31:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	construct_child_after_pipe(t_ast **ast, char *tmp, bool *is_child)
{
	(*ast)->next = create_ast_node(ft_strdup(tmp), PIPE);
	free(tmp);
	(*ast)->next->parent = (*ast)->parent;
	(*ast)->next->prev = (*ast);
	(*ast) = (*ast)->next;
	*is_child = false;
}

void	construct_child_before_pipe(t_ast **ast, char *tmp, bool *is_child)
{
	(*ast)->child = create_ast_node(ft_strdup(tmp), PIPE);
	free(tmp);
	(*ast)->child->parent = (*ast);
	(*ast) = (*ast)->child;
	*is_child = false;
}

void	eldest_child(t_ast **ast, t_token **tokens, bool *create_sibling)
{
	(*ast)->child = create_ast_node(ft_strdup((*tokens)->cmd), 0);
	(*ast)->child->parent = (*ast);
	(*ast) = (*ast)->child;
	if ((*tokens)->type == DOLLAR)
	{
		(*ast)->type = DOLLAR;
		dollar_deal((*ast), create_sibling);
	}
	else
		(*ast)->type = CMD;
	if ((*tokens)->next != NULL && (*tokens)->next->type != PIPE)
		*create_sibling = true;
}

void	sibling(t_ast **ast, t_token **tokens, bool *create_sibling)
{
	(*ast)->next = create_ast_node(ft_strdup((*tokens)->cmd), 0);
	(*ast)->next->parent = (*ast)->parent;
	(*ast)->next->prev = (*ast);
	(*ast) = (*ast)->next;
	if ((*tokens)->type == DOLLAR)
	{
		(*ast)->type = DOLLAR;
		dollar_deal((*ast), create_sibling);
	}
}

void	construct_sibling(t_ast **ast, t_token **tokens, bool *create_sibling)
{
	if (*create_sibling == false)
		eldest_child(ast, tokens, create_sibling);
	else if (*create_sibling == true)
		sibling(ast, tokens, create_sibling);
}
