/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 05:36:16 by codespace         #+#    #+#             */
/*   Updated: 2024/09/16 14:24:46 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*create_exec_node(char **cmd, int *type)
{
	t_exec	*new_node;

	new_node = ft_calloc(1, sizeof(t_exec));
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->infile = 0;
	new_node->outfile = 0;
	new_node->fd[0] = 0;
	new_node->fd[1] = 0;
	return (new_node);
}

t_exec	*join_exec_nodes(t_exec *exec, char **cmd, int *type)
{
	t_exec	*new_node;

	new_node = create_exec_node(cmd, type);
	if (!new_node)
		return (NULL);
	if (!exec)
		return (new_node);
	exec->next = new_node;
	new_node->prev = exec;
	return (new_node);
}

// printf("cmd[1]: %s\n", exec->cmd[1]);
void	free_exec(t_exec *exec)
{
	t_exec	*tmp;
	int		i;

	while (exec)
	{
		tmp = exec->next;
		i = 0;
		while ((exec->cmd && exec->cmd[i]))
		{
			free(exec->cmd[i]);
			i++;
		}
		i = 0;
		while (exec->cmd_list && exec->cmd_list[i])
		{
			free(exec->cmd_list[i]);
			i++;
		}
		free(exec->type);
		free(exec->cmd);
		free(exec->cmd_list);
		free(exec);
		exec = tmp;
	}
}

void	print_exec(t_exec *exec)
{
	t_exec	*tmp;
	int		i;

	tmp = exec;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			printf("cmd[%d]: %s\n", i, tmp->cmd[i]);
			printf("current:%p\n", tmp);
			printf("next:%p\n", tmp->next);
			printf("prev:%p\n", tmp->prev);
			i++;
		}
		tmp = tmp->next;
	}
}
