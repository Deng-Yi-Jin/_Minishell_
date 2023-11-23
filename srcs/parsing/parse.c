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
	t_token	**tmp_token;
	char	*tmp;
	bool	is_child;

	tmp = "";
	(*tokens) = lst_first_last(*tokens, false);
	ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = NULL;
	(*ast) = create_ast_node(NULL);
	while ((*tokens)->cmd != NULL)
	{
		is_child = true;
		while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
		{
			tmp = ft_strjoin(tmp, (*tokens)->cmd);
			(*tokens) = (*tokens)->next;
		}
		*tokens = lst_go_back(*tokens);
		while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
		{
			// printf("cmd: %s %p\n", (*tokens)->cmd, (*tokens)->prev);  rm -rf valorant
			if (is_child == true && (*tokens)->prev != NULL && (*tokens)->prev->type == PIPE)
			{
				(*ast)->next_child = create_ast_node(ft_strdup(tmp));
				free(tmp);
				tmp = "";
				(*ast)->next_child->parent = (*ast);
				(*ast)->next_child->prev_child = (*ast);
				(*ast) = (*ast)->next_child;
				is_child = false;
			}
			if (is_child == true)
			{
				(*ast)->next_child = create_ast_node(ft_strdup(tmp));
				free(tmp);
				tmp = "";
				(*ast)->next_child->parent = (*ast);
				(*ast) = (*ast)->next_child;
				is_child = false;
			}
			if ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
			{
				(*ast)->next_grandchild = create_ast_node(ft_strdup((*tokens)->cmd));
				(*ast)->next_grandchild->prev_grandchild = (*ast);
				(*ast) = (*ast)->next_grandchild;
				(*tokens) = (*tokens)->next;
			}

		}
		if ((*tokens)->type == PIPE)
		{
			(*ast) = ast_first_last((*ast), true, false);
			(*tokens) = (*tokens)->next;
		}
	}
	// while ((*tokens)->cmd != NULL)
	// {
	// 	if ((*tokens)->prev == NULL && (*tokens)->type != PIPE)
	// 	{
	// 		(*ast)->next_child = create_ast_node(ft_strdup((*tokens)->cmd));
	// 		(*ast)->next_child->parent = (*ast);
	// 		(*ast) = (*ast)->next_child;
	// 		(*tokens) = (*tokens)->next;
	// 	}
	// 	if ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
	// 	{
	// 		(*ast)->next_grandchild = create_ast_node(ft_strdup((*tokens)->cmd));
	// 		(*ast)->next_grandchild->prev_grandchild = (*ast);
	// 		(*ast) = (*ast)->next_grandchild;
	// 	}
	// 	else if ((*tokens)->type == PIPE)
	// 	{
	// 		(*tokens) = (*tokens)->next;
	// 		(*ast) = ast_first_last((*ast), true, false);
	// 		(*ast)->next_child = create_ast_node(ft_strdup((*tokens)->cmd));
	// 		(*ast)->next_child->parent = (*ast)->parent;
	// 		(*ast)->next_child->prev_child = (*ast);
	// 		(*ast) = (*ast)->next_child;
	// 	}
	// 	(*tokens) = (*tokens)->next;
	// }
	(*ast) = ast_first_last(*ast, true, true);
	print_ast_all(ast);
	free_ast(ast);
	free(ast);
}

