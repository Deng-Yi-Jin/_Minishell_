/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_execute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 04:03:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 18:04:32 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*dollar_execute(t_ast *ast, t_token *command)
{
	t_ast	*current_node;
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_calloc(2, sizeof(char *));
	current_node = ast->child;
	while (current_node)
	{
		if (current_node->type == CMD)
		{
			cmd[i] = ft_strdup(current_node->cmd);
			i++;
		}
		
	}
}
