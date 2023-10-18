/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:33:37 by root              #+#    #+#             */
/*   Updated: 2023/10/14 14:36:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_ast	*create_ast_node(char *cmd)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->value = NULL;
	new_node->type = 0;
	new_node->next_sibling = NULL;
	new_node->prev_sibling = NULL;
	new_node->token = NULL;
	new_node->right = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->parent = NULL;
	return (new_node);
}

t_ast	*add_ast(t_ast	*ast, char *cmd)
{
	t_ast	*new_node;

	new_node = create_ast_node(cmd);
	if (!ast)
		return (new_node);
	if (!new_node)
		return (NULL);
	ast->next = new_node;
	new_node->prev = ast;
	return (new_node);
}

t_ast	*ast_first_last(t_ast *ast, bool is_last)
{
	if (is_last == true)
	{
		while (ast->next != NULL && ast != NULL)
			ast = ast->next;
		return (ast);
	}
	while (ast->prev != NULL && ast != NULL)
		ast = ast->prev;
	return (ast);
}

void	free_ast(t_ast **ast)
{
	t_ast	*tmp;

	(*ast) = ast_first_last(*ast, false);
	while (*ast)
	{
		tmp	= (*ast)->next;
		free((*ast)->cmd);
		free(*ast);
		*ast = tmp;
	}
}

void print_ast(t_ast *ast)
{
	printf("cmd: %s\n", ast->cmd);
	printf("value: %s\n", ast->value);
	printf("type: %d\n", ast->type);
	printf("next_sibling: %p\n", ast->next_sibling);
	printf("prev_sibling: %p\n", ast->prev_sibling);
	printf("token: %p\n", ast->token);
	printf("right: %p\n", ast->right);
	printf("prev: %p\n", ast->prev);
	printf("next: %p\n", ast->next);
	printf("parent: %p\n", ast->parent);
}

void print_ast_all(t_ast **ast)
{
	t_ast *tmp;

	tmp = *ast;
	while (tmp)
	{
		print_ast(tmp);
		tmp = (tmp)->next;
	}
}