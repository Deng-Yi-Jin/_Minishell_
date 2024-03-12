/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_execute_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 04:03:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/12 06:40:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	execute_cmd(char **cmd, char **envp)
{
	int		pipe_fd[2];
	char	*command_path;
	char	*line;
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		perror("pipe");
	if (pid = fork() == -1)
		perror("fork");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		command_path = get_command_path(cmd[0], envp);
		if (command_path == NULL)
		{
			if (match_cmd(cmd[0], cmd, envp) == false)
				printf("Command not found: %s\n", cmd[0]);
		}
		else
		{
			if (execve(command_path, cmd, envp))
				perror("execve");
		}
	}
	else
	{
		close(pipe_fd[1]);
		// line = get_next_line(pipe_fd[0]);
		// while ()
	}
}

char	*execute_dollar_expansion(t_ast *ast, char **envp)
{
	char	**cmd;
	t_ast	*current_node;
	t_count	count;

	count = (t_count){0, 0, 0, 0};
	current_node = ast->child;
	cmd = ft_calloc(2, sizeof(char *));
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
	execute_cmd(cmd, envp);
}
