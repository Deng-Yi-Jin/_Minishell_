/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:06:59 by geibo             #+#    #+#             */
/*   Updated: 2024/09/12 16:59:25 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	traverse(t_ast **ast, void (*f)(void *), int depth, bool print)
{
	t_ast	*temp;

	if (*ast == NULL)
		return (false);
	if (print == false && (*ast)->cmd != NULL)
		// printf("%s\n", (*ast)->cmd);
	temp = (*ast)->next;
	traverse(&((*ast)->child), f, depth + 1, print);
	f((*ast)->cmd);
	f((*ast));
	traverse(&temp, f, depth, print);
	return (true);
}

bool	add_cmd_to_db_lst(t_ast **ast, t_exec *exec, int depth)
{
	t_ast	*temp;
	t_ast	*current_temp;
	t_count	count;

	count = (t_count){0, 0, 0};
	if (*ast == NULL)
		return (false);
	temp = (*ast)->next;
	if ((*ast)->child == NULL)
	{
		exec = join_exec_nodes(exec, ft_calloc(2, sizeof(char *)), NULL);
		current_temp = *ast;
		while (current_temp != NULL)
		{
			exec->cmd[count.i++] = current_temp->cmd;
			if (current_temp->next == NULL)
				break ;
			current_temp = current_temp->next;
		}
	}
	add_cmd_to_db_lst(&((*ast)->child), exec, depth + 1);
	add_cmd_to_db_lst(&temp, exec, depth);
	return (true);
}

bool	execute_dollar(t_ast **ast, int depth, char **envp)
{
	t_ast	*temp;

	if (*ast == NULL)
		return (false);
	temp = (*ast)->next;
	execute_dollar(&((*ast)->child), depth + 1, envp);
	if ((*ast)->type == DOLLAR)
	{
		printf("DOLLAR\n");
		(*ast)->type = CMD;
		(*ast)->cmd = execute_dollar_expansion(*ast, envp);
	}
	execute_dollar(&temp, depth, envp);
	return (true);
}
