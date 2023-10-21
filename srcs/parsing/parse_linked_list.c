/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:33:37 by root              #+#    #+#             */
/*   Updated: 2023/10/21 15:48:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*add_db_node(t_ast *ast)
{
	t_ast	**new_db;

	new_db = (t_ast **)malloc(sizeof(t_ast *));
	(*new_db) = NULL;
	ast->next = (*new_db);
	(*new_db)->prev = ast;
	return (*new_db);
}

t_ast	*create_ast_node(char *cmd)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->type = 0;
	new_node->next_grandchild = NULL;
	new_node->prev_grandchild = NULL;	
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->parent = NULL;
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

t_ast	*add_child(t_ast *ast, char *cmd)
{
	t_ast	*new_ast;

	new_ast = create_ast_node(cmd);
	if (!new_ast)
		return (NULL);
	if (ast == NULL)
		return (new_ast);
	ast->next_grandchild = new_ast;
	new_ast->prev_grandchild = ast;
	return (new_ast);
}

t_ast	*add_last_child(t_ast *ast, char *cmd)
{
	t_ast	*new_ast;

	new_ast = create_ast_node(cmd);
	if (!new_ast)
		return (NULL);
	if (ast == NULL)
		return (new_ast);
	ast->next_grandchild = NULL;
	new_ast->prev_grandchild = ast;
	return (new_ast);
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
	printf("type: %d\n", ast->type);
	printf("next_sibling: %p\n", ast->next_grandchild);
	printf("prev_sibling: %p\n", ast->prev_grandchild);
	printf("prev: %p\n", ast->prev);
	printf("next: %p\n", ast->next);
	printf("parent: %p\n", ast->parent);
}

void print_ast_all(t_ast **ast)
{
	if (*ast == NULL)
		return;
	print_ast(*ast);
	if ((*ast)->next_grandchild != NULL)
		print_ast_all(&((*ast)->next_grandchild));
	if ((*ast)->next != NULL)
		print_ast_all(&((*ast)->next));
}