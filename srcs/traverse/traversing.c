/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:03:36 by codespace         #+#    #+#             */
/*   Updated: 2024/09/16 14:35:02 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*process_ast_node(t_ast **ast, t_exec *exec, t_traverse *utils)
{
	t_ast	*go_to_history;
	t_ast	*go_to_pipe;

	utils->n_cmd = 0;
	utils->word = 0;
	go_to_pipe = *ast;
	while (*ast && (*ast)->child != NULL)
		*ast = (*ast)->child;
	go_to_history = *ast;
	count_commands(ast, utils);
	*ast = go_to_history;
	exec = join_exec_nodes(exec, ft_calloc(utils->n_cmd + 1, sizeof(char *)),
			NULL);
	process_commands(ast, exec, utils);
	*ast = go_to_pipe;
	return (exec);
}

void	count_commands(t_ast **ast, t_traverse *utils)
{
	while (*ast)
	{
		utils->n_cmd++;
		if ((*ast)->next == NULL)
			break ;
		*ast = (*ast)->next;
	}
}

void	process_commands(t_ast **ast, t_exec *exec, t_traverse *utils)
{
	while (*ast)
	{
		exec->cmd[utils->word] = ft_strdup((*ast)->cmd);
		if ((*ast)->next == NULL)
			break ;
		*ast = (*ast)->next;
		utils->word++;
	}
}

t_exec	*executing(t_ast **ast, t_exec *exec)
{
	t_exec		*head;
	t_traverse	utils;

	head = 0;
	utils.is_pipe = true;
	exec = 0;
	(*ast) = (*ast)->child;
	while (*ast)
	{
		exec = process_ast_node(ast, exec, &utils);
		if (!head)
			head = exec;
		if ((*ast)->next == NULL)
			break ;
		*ast = (*ast)->next;
	}
	return (head);
}
