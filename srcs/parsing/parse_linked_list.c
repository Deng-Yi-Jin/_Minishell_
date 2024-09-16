/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:33:37 by root              #+#    #+#             */
/*   Updated: 2024/09/16 13:45:24 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

t_ast	*create_ast_node(char *cmd, int type)
{
	t_ast	*new_node;
	char	*tmp;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->type = type;
	new_node->child = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
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
	new_node->child = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->parent = NULL;
	return (new_node);
}

// create test for traverse
void	custom_print1(void *cmd)
{
	printf("%s\n", (char *)cmd);
}

// void test_traverse(void)
// {
//     // Your test function with the updated traverse function
//     t_ast *node1 = malloc(sizeof(t_ast));
//     t_ast *node2 = malloc(sizeof(t_ast));
//     t_ast *node3 = malloc(sizeof(t_ast));
//     t_ast *node4 = malloc(sizeof(t_ast));
//     t_ast *node5 = malloc(sizeof(t_ast));
//     t_ast *node6 = malloc(sizeof(t_ast));
// 	t_ast *node7 = malloc(sizeof(t_ast));
// 	t_ast *node8 = malloc(sizeof(t_ast));
// 	t_ast *node9 = malloc(sizeof(t_ast));
// 	t_ast *node10 = malloc(sizeof(t_ast));

//     // Set up your tree structure here...
// 	node1->cmd = "command1";
//     node1->next = node2;
//     node1->child = node4;

//     node2->cmd = "command2";
//     node2->next = node3;
//     node2->child = NULL;

//     node3->cmd[0] = "command3";
//     node3->next = NULL;
//     node3->child = node8;

//     node4->cmd[0] = "child1";
//     node4->next = node5;
//     node4->child = NULL;

//     node5->cmd[0] = "child2";
//     node5->next = node6;
//     node5->child = node7;

//     node6->cmd[0] = "child3";
//     node6->next = NULL;
//     node6->child = NULL;

//     node7->cmd[0] = "grandchild1";
//     node7->next = NULL;
//     node7->child = NULL;

//     node8->cmd = "child4";
//     node8->next = node9;
//     node8->child = node10;

//     node9->cmd = "grandchild2";
//     node9->next = NULL;
//     node9->child = NULL;

//     node10->cmd = "grandchild3";
//     node10->next = NULL;
//     node10->child = NULL;

//     printf("Fancy Tree Output:\n");
//     traverse(&node1, free, 0, true);

//     // Free the memory
//     // free_nodes(node1);

//     return ;
// }

// void	free_ast(t_ast **ast)
// {
// 	t_ast	*tmp;
// 	t_ast	*child_tmp;

// 	while ((*ast) && (*ast)->next_grandchild != NULL)
// 		(*ast) = (*ast)->next_grandchild;
// 	while ((*ast) && (*ast)->prev_grandchild != NULL)
// 	{
// 		(*ast) = (*ast)->prev_grandchild;
// 		tmp = (*ast)->next_grandchild;
// 		free(tmp->cmd);
// 		free(tmp);
// 	}
// 	if ((*ast) && (*ast)->next_child != NULL)
// 	{
// 		tmp = (*ast);
// 		(*ast) = (*ast)->next_child;
// 		free(tmp->cmd);
// 		free(tmp);
// 		free_ast(&(*ast));
// 	}
// 	else if ((*ast) && (*ast)->next_child == NULL)
// 	{
// 		tmp = (*ast);
// 		(*ast) = (*ast)->parent;
// 		free(tmp->cmd);
// 		free(tmp);
// 	}
// }

// void print_ast(t_ast *ast)
// {
// 	printf("cmd: %s\n", ast->cmd);
// 	printf("pipe_cmd: %s\n", ast->parent->cmd);
// 	printf("type: %d\n", ast->type);
// 	printf("Current address:%p\n", ast);
// 	printf("next_sibling: %p\n", ast->next);
// 	printf("prev_sibling: %p\n", ast->prev);
// 	printf("child: %p\n", ast->child);
// 	printf("parent: %p\n", ast->parent);
// 	printf("big boss: %p\n", ast->parent->parent);
// }

// void 	print_ast_all(t_ast **ast)
// {
// 	if ((*ast) == NULL || (*ast)->cmd == NULL)
// 		return ;
// 	// (*ast) = ast_first_last(*ast, false, false);
// 	print_ast(*ast);
// 	// if ((*ast)->next_grandchild != NULL)
// 	// {
// 	print_ast_all(&(*ast)->next_grandchild);
// 	// else if ((*ast)->next_child != NULL)
// 	// {
// 	// printf("CHILD BABY\n");
// 	// printf("%s\n", (*ast)->next_child->cmd);
// 	print_ast_all(&(*ast)->next_child);
// 	// if ((*ast)->next_grandchild != NULL)
// 	// 	print_ast_all(&((*ast)->next_)grandchild));
// 	// if ((*ast)->next_grandchild == NULL)
// 	// {
// 	// 	(*ast) = ast_first_last(*ast, true, false);
// 	// 	(*ast) = (*ast)->next_child;
// 	// 	print_ast_all(&((*ast)->next_child));
// 	// }
// }