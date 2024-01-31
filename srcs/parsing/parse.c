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

void custom_print(void *cmd)
{
	printf("%s", (char *)cmd);
}

void	parse(t_token **tokens, char **envp)
{
	t_ast	**ast;
	t_ast	*ast_tmp;
	t_ast	*minishell;
	t_exec	*exec;
	char	*tmp;
	bool	is_child;
	bool	create_sibling;

	(*tokens) = lst_first_last(*tokens, false);
	ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = NULL;
	(*ast) = create_parent_node(NULL);
	minishell = (*ast);
	while ((*tokens)->cmd != NULL)
	{
		is_child = true;
		create_sibling = false;
		tmp = ft_calloc(1, sizeof(char));
		while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
		{
			tmp = ft_strjoin(tmp, (*tokens)->cmd);
			(*tokens) = (*tokens)->next;
		}
		*tokens = lst_go_back(*tokens);
		while ((*tokens)->type != PIPE && (*tokens)->cmd != NULL)
		{
			if (is_child == true && (*tokens)->prev != NULL && (*tokens)->prev->type == PIPE)
			{
				(*ast)->next = create_ast_node(ft_strdup(tmp), PIPE);
				free(tmp);
				(*ast)->next->parent = (*ast)->parent;
				(*ast)->next->prev = (*ast);
				(*ast) = (*ast)->next;
				is_child = false;
			}
			else if (is_child == true)
			{
				(*ast)->child = create_ast_node(ft_strdup(tmp), PIPE);
				free(tmp);
				(*ast)->child->parent = (*ast);
				(*ast) = (*ast)->child;
				is_child = false;
			}
			if ((*tokens)->type != PIPE && (*tokens)->cmd != NULL && is_child == false)
			{
				if (create_sibling == false)
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
						create_sibling = true;
				}
				else if (create_sibling == true)
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
				(*tokens) = (*tokens)->next;
			}
		//	print_ast((*ast));
		}
		if ((*tokens)->type == PIPE)
		{
			(*ast) = (*ast)->parent;
			(*tokens) = (*tokens)->next;
		}
	}
	while ((*ast)->parent != NULL)
		(*ast) = (*ast)->parent;
	minishell = (*ast);
	exec = executing(ast, exec);
	if (exec->next == NULL)
		execute_single_cmd(exec, envp);
	// else
	// 	execution(exec, envp);
	else
		execute(exec, envp);
	free_exec(exec);
	(*ast) = minishell;
	traverse(ast, free, 0, false); 
	free(ast);
}