/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:59:30 by codespace         #+#    #+#             */
/*   Updated: 2024/08/26 18:24:31 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This is the child process
// Close the read end of the pipe in the child
// Replace stdout with the write end of the pipe
// This is the parent process
// Close the write end of the pipe in the parent
// Replace stdin with the read end of the pipe
void	exec_pipe(t_exec *exec, char **envp, char *command_path)
{
	while (exec->next != NULL)
	{
		if (pipe(exec->fd) == -1)
			perror("pipe");
		exec->pid = fork();
		if (exec->pid == -1)
			perror("fork");
		if (exec->pid == 0)
		{
			close(exec->fd[0]);
			dup2(exec->fd[1], STDOUT_FILENO);
			execve(command_path, exec->cmd, envp);
			exit(0);
		}
		else
		{
			waitpid(exec->pid, NULL, 0);
			close(exec->fd[1]);
			dup2(exec->fd[0], STDIN_FILENO);
		}
		if (command_path != NULL)
			free(command_path);
		exec = exec->next;
		command_path = find_command_path(exec->cmd[0], envp);
	}
	if (command_path == NULL)
	{
		if (execute_builtin(exec->cmd[0], exec->cmd, envp) == false)
			printf("Command not found: %s\n", exec->cmd[0]);
	}
	else
	{
		exec->pid = fork();
		if (exec->pid == 0)
		{
			if (execve(command_path, exec->cmd, envp))
				perror("execve");
		}
		else
			waitpid(exec->pid, NULL, 0);
	}
	if (command_path != NULL)
		free(command_path);
	exec = exec->next;
}
