/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_execute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 04:03:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 05:30:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*dollar_execute(t_ast *ast, t_token *command)
{
	t_ast	*current_node;

	current_node = ast->child;
	while (current_node)
	{
		if (current_node->type == CMD)
		{
			command = add_tokens(command, ft_strdup(current_node->cmd), CMD);
			if (current_node->next == NULL)
				break;
			current_node = current_node->next;
		}
		else if (current_node->type == DOLLAR)
			current_node = dollar_execute(current_node->child, command);
	}
}
