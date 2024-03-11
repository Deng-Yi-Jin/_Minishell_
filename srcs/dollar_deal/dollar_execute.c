/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:40:07 by geibo             #+#    #+#             */
/*   Updated: 2024/03/10 20:11:57 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_expansion(t_ast **ast)
{
	t_ast	*current_node;
	t_ast	*sibling;
	bool	is_dollar;

	current_node = (*ast)->child;
	sibling = NULL;
	while (current_node)
	{
		is_dollar = true;
		if (sibling == NULL)
			sibling = (*ast)->child;
		else
			sibling = sibling->next;
	}
}
