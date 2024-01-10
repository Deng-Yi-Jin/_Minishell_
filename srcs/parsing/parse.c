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
	t_ast	*ast_tmp;
	t_ast	*minishell;
	char	*tmp;
	bool	is_child;

	(*tokens) = lst_first_last(*tokens, false);
	ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = NULL;
	(*ast) = create_parent_node(NULL);
	minishell = (*ast);
	while ((*tokens)->cmd != NULL)
	{
		is_child = true;
		tmp = ft_calloc(1, sizeof(char));
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
				(*ast)->next_child = create_ast_node(ft_strdup(tmp), PIPE);
				free(tmp);
				(*ast)->next_child->parent = (*ast);
				(*ast)->next_child->prev_child = (*ast);
				(*ast) = (*ast)->next_child;
				is_child = false;
			}
			if (is_child == true)
			{
				(*ast)->next_child = create_ast_node(ft_strdup(tmp), PIPE);
				free(tmp);
				(*ast)->next_child->parent = (*ast);
				(*ast) = (*ast)->next_child;
				is_child = false;
			}
			if ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
			{
				(*ast)->next_grandchild = create_ast_node(ft_strdup((*tokens)->cmd), 0);
				(*ast)->next_grandchild->prev_grandchild = (*ast);
				(*ast) = (*ast)->next_grandchild;
				if ((*tokens)->type == REDIR_IN || (*tokens)->type == REDIR_OUT
				|| (*tokens)->type == REDIR_OUT_APPEND || (*tokens)->type == HERE_DOC
				|| (*tokens)->type == DOLLAR)
					(*ast)->type = (*tokens)->type;
				(*tokens) = (*tokens)->next;
			}
		}
		if ((*tokens)->type == PIPE)
		{
			(*ast) = ast_first_last((*ast), true, false);
			dollar_deal(ast);
			(*ast) = ast_first_last((*ast), true, false);
			(*tokens) = (*tokens)->next;
		}
	}
	(*ast) = ast_first_last(*ast, true, true);
	//print_ast_all(ast);
	free_ast(ast);
	free(minishell);
	free(ast);
}

