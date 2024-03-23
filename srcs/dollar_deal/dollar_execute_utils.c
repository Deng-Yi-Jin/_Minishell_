/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_execute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 04:03:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/20 16:11:10 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*matching_cmd(char **cmd, char **envp)
{
	char	*result;
	t_count	count;

	count = (t_count){1, 1, 1, 1};
	if (ft_strcmp(cmd[0], "echo"))
	{
		while(cmd[count.i])
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
	char		*command_path;
	t_count		count;
	char		*result;
	size_t		bytesRead;

	count = (t_count){0, 0, 0, 0};
	// if (ft_strcmp(cmd[0], "echo"))
	// {
	// 	result = matching_cmd(cmd, envp);
	// 	return (result);
	// }
	command_path = find_command_path(cmd[0], envp);
	if (command_path == NULL)
	{
		if (match_cmd(cmd[0], cmd, envp))
			return (NULL);
	}
	if (pipe(execute.fd) == -1)
	{
		perror("pipe");
		return (NULL);
	}
	if ((execute.pid = fork()) == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (execute.pid == 0)
	{
		close(execute.fd[0]);
		dup2(execute.fd[1], 1);
		execve(command_path, cmd, envp);
		exit(0);
	}
	else
	{
		close(execute.fd[1]);
		result = ft_calloc(BUFFER_SIZE, sizeof(char));
		bytesRead = read(execute.fd[0], result, BUFFER_SIZE - 1);
		result[bytesRead] = '\0';
		while (count.i < bytesRead)
		{
			if (result[count.i] == '\n')
				result[count.i] = '\t';
			count.i++;
		}
		close(execute.fd[0]);
		waitpid(execute.pid, NULL, 0);
	}
	free(command_path);
	return (result);
}

char	*execute_dollar_expansion(t_ast *ast, char **envp)
{
	char	**cmd;
	char	*result;
	t_ast	*current_node;
	t_count	count;

	count = (t_count){0, 0, 0, 0};
	current_node = ast->child;
	while (current_node)
	{
		count.strlen++;
		current_node = current_node->next;
	}
	current_node = ast->child;
	cmd = ft_calloc(count.strlen + 1, sizeof(char *));
	while (current_node)
	{
		if (current_node->type == DOLLAR)
			cmd[count.i++] = execute_dollar_expansion(current_node, envp);
		else if (current_node->type == CMD)
			cmd[count.i++] = ft_strdup(current_node->cmd);
		else if (current_node->type == WORD)
			cmd[count.i++] = ft_strdup(current_node->cmd);
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
	while (cmd[count.j])
		free(cmd[count.j++]);
	free(cmd);
	return (ast->cmd);
}
