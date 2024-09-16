/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_execute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 04:03:10 by codespace         #+#    #+#             */
/*   Updated: 2024/09/16 09:52:36 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ast_len(t_ast *ast)
{
	t_count	count;
	t_ast	*current_node;

	count = (t_count){0, 0, 0, 0};
	current_node = ast->child;
	while (current_node)
	{
		count.strlen++;
		current_node = current_node->next;
	}
	return (count.strlen);
}

char	*add_cmd(t_ast *current_node, char **envp)
{
	static int	i;

	i = 0;
	if (current_node->type == DOLLAR)
		return (execute_dollar_expansion(current_node, envp));
	else if (current_node->type == CMD)
		return (ft_strdup(current_node->cmd));
	else if (current_node->type == WORD)
		return (ft_strdup(current_node->cmd));
}

char	*matching_cmd(char **cmd)
{
	char	*result;
	t_count	count;

	count = (t_count){1, 1, 1, 1};
	if (ft_strcmp(cmd[0], "echo"))
	{
		while (cmd[count.i])
		{
			result = ft_strjoin(result, cmd[count.i]);
			count.i++;
		}
	}
	return (result);
}

char	*executing_cmd(char **cmd, char **envp)
{
	t_execute	execute;
	char		*result;
	char		*command_path;

	command_path = find_command_path(cmd[0], envp);
	if (command_path == NULL)
	{
		if (execute_builtin(cmd[0], cmd, envp))
			return (NULL);
	}
	if (pipe(execute.fd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	result = handle_fork(&execute, command_path, cmd, envp);
	return (result);
}

char	*execute_dollar_expansion(t_ast *ast, char **envp)
{
	char	**cmd;
	char	*result;
	t_ast	*current_node;
	int		i;

	i = 0;
	current_node = ast->child;
	cmd = ft_calloc(ast_len(ast) + 1, sizeof(char *));
	while (current_node)
	{
		cmd[i++] = add_cmd(current_node, envp);
		current_node = current_node->next;
	}
	if (ast && ast->cmd)
	{
		result = executing_cmd(cmd, envp);
		if (result != NULL)
		{
			free(ast->cmd);
			ast->cmd = ft_strdup(result);
			free(result);
		}
	}
	free_split(cmd);
	return (ast->cmd);
}

/*executingcmd execute_builtin*/