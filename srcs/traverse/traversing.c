/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:03:36 by codespace         #+#    #+#             */
/*   Updated: 2024/05/21 14:07:48 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*executing(t_ast **ast, t_exec *exec)
{
	t_exec	*head;
	t_ast	*go_to_history;
	t_ast	*go_to_pipe;
	int		n_cmd;
	int		word;
	bool	is_pipe;

	head = 0;
	is_pipe = true;
	exec = 0;
	(*ast) = (*ast)->child;
	while ((*ast))
	{
		n_cmd = 0;
		word = 0;
		go_to_pipe = (*ast);
		while ((*ast) && (*ast)->child != NULL)
			(*ast) = (*ast)->child;
		go_to_history = (*ast);
		while ((*ast))
		{
			n_cmd++;
			if ((*ast)->next == NULL)
				break;
			(*ast) = (*ast)->next;
		}
		(*ast) = go_to_history;
		exec = join_exec_nodes(exec, ft_calloc(n_cmd + 1, sizeof(char *)));
		if (!head)
			head = exec;
		while (*ast)
		{
			exec->cmd[word] = ft_strdup((*ast)->cmd);
			if ((*ast)->next == NULL)
				break;
			(*ast) = (*ast)->next;
			word++;
		}
		(*ast) = go_to_pipe;
		if ((*ast)->next == NULL)
			break;
		(*ast) = (*ast)->next;
	}
	return (head);
}
