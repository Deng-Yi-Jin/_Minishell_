/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:36:16 by codespace         #+#    #+#             */
/*   Updated: 2024/07/19 00:22:53 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*create_exec_node(char **cmd)
{
	t_exec	*new_node;

	new_node = ft_calloc(1, sizeof(t_exec));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->infile = 0;
	new_node->outfile = 0;
	new_node->fd[0] = 0;
	new_node->fd[1] = 0;
	return (new_node);
}

t_exec *join_exec_nodes(t_exec *exec, char **cmd)
{
	t_exec *new_node;

	new_node = create_exec_node(cmd);
	if (!new_node)
		return (NULL);
	if (!exec)
		return (new_node);
	exec->next = new_node;
	new_node->prev = exec;
	return (new_node);
}

void	free_exec(t_exec *exec)
{
	t_exec *tmp;
	int		i;

	while (exec)
	{
		tmp = exec->next;
		i = 0;
		while (exec->cmd[i])
		{
			// printf("cmd[1]: %s\n", exec->cmd[1]);
			free(exec->cmd[i]);
			i++;
		}
		free(exec->cmd);
		free(exec);
		exec = tmp;
	}
}

void	print_exec(t_exec *exec)
{
	printf("cmd:%s\n", exec->cmd[0]);
	printf("cmd:%s\n", exec->cmd[1]);
	printf("current:%p\n", exec);
	printf("next:%p\n", exec->next);
	printf("prev:%p\n", exec->prev);
}
