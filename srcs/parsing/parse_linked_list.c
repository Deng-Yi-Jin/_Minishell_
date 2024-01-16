/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:33:37 by root              #+#    #+#             */
/*   Updated: 2024/01/16 07:08:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast_node(char *cmd, int type)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->type = type;
	new_node->next_grandchild = NULL;
	new_node->prev_grandchild = NULL;	
	new_node->prev_child = NULL;
	new_node->next_child = NULL;
	new_node->parent = NULL;
	return (new_node);
}

t_ast	*create_parent_node(char *cmd)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->next_grandchild = NULL;
	new_node->prev_grandchild = NULL;	
	new_node->prev_child = NULL;
	new_node->next_child = NULL;
	new_node->parent = NULL;
	return (new_node);
}

t_ast	*ast_first_last(t_ast *ast, bool go_child, bool go_sibling)
{
	if (go_child == true)
	{
		while ((ast)->prev_grandchild != NULL && (ast) != NULL)
		{
			(ast) = (ast)->prev_grandchild;
			// printf("%s\n", (ast)->cmd);
		}	
	}
	if (go_sibling == true)
	{
		while ((ast)->prev_child != NULL && (ast))
			(ast) = (ast)->prev_child;
	}
	return (ast);
}

t_ast	*ast_first(t_ast *ast, bool go_child, bool go_sibling)
{
	if (go_child == true)
	{
		while ((ast)->prev_grandchild != NULL)
		{
			(ast) = (ast)->prev_grandchild;
		}	
	}
	if (go_sibling == true)
	{
		while ((ast)->prev_child != NULL)
		{
			(ast) = (ast)->prev_child;
		}
	}
	return (ast);
}

void	free_ast(t_ast **ast)
{
	t_ast	*tmp;
	t_ast	*child_tmp;

	while ((*ast) && (*ast)->next_grandchild != NULL)
		(*ast) = (*ast)->next_grandchild;
	while ((*ast) && (*ast)->prev_grandchild != NULL)
	{
		(*ast) = (*ast)->prev_grandchild;
		tmp = (*ast)->next_grandchild;
		free(tmp->cmd);
		free(tmp);
	}
	if ((*ast) && (*ast)->next_child != NULL)
	{
		tmp = (*ast);
		(*ast) = (*ast)->next_child;
		free(tmp->cmd);
		free(tmp);
		free_ast(&(*ast));
	}
	else if ((*ast) && (*ast)->next_child == NULL)
	{
		tmp = (*ast);
		(*ast) = (*ast)->parent;
		free(tmp->cmd);
		free(tmp);
	}
}

void print_ast(t_ast *ast)
{
	printf("cmd: %s\n", ast->cmd);
	printf("type: %d\n", ast->type);
	printf("Current address:%p\n", ast);
	printf("next_sibling: %p\n", ast->next_grandchild);
	printf("prev_sibling: %p\n", ast->prev_grandchild);
	printf("prev: %p\n", ast->prev_child);
	printf("next: %p\n", ast->next_child);
	printf("parent: %p\n", ast->parent);
}

void 	print_ast_all(t_ast **ast)
{
	if ((*ast) == NULL || (*ast)->cmd == NULL)
		return ;
	// (*ast) = ast_first_last(*ast, false, false);
	print_ast(*ast);
	
	// if ((*ast)->next_grandchild != NULL)
	// {
	print_ast_all(&(*ast)->next_grandchild);
	// else if ((*ast)->next_child != NULL)
	// {
	// printf("CHILD BABY\n");
	// printf("%s\n", (*ast)->next_child->cmd);
	print_ast_all(&(*ast)->next_child);
	// if ((*ast)->next_grandchild != NULL)	
	// 	print_ast_all(&((*ast)->next_)grandchild));
	// if ((*ast)->next_grandchild == NULL)
	// {
	// 	(*ast) = ast_first_last(*ast, true, false);
	// 	(*ast) = (*ast)->next_child;
	// 	print_ast_all(&((*ast)->next_child));
	// }
}

int	num_of_pipes(t_token **tokens)
{
	int	pipe;

	pipe = 0;
	while ((*tokens)->cmd != NULL && (*tokens))
	{
		if ((*tokens)->type == PIPE)
			pipe++;
		(*tokens) = (*tokens)->next;
	}
	(*tokens) = lst_first_last(*tokens, false);
	return (pipe);
}
