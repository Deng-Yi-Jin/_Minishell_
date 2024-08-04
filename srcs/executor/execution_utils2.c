/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:59:30 by codespace         #+#    #+#             */
/*   Updated: 2024/02/07 10:23:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pipe(t_exec *exec, char **envp, char *command_path)
{
	while (exec->next != NULL)
	{
		if (pipe(exec->fd) == -1)
			perror("pipe");
		exec->pid = fork();
		if (exec->pid == -1)
			perror("fork");
		if (exec->pid == 0) // This is the child process
		{
			close(exec->fd[0]); // Close the read end of the pipe in the child
			dup2(exec->fd[1], STDOUT_FILENO); // Replace stdout with the write end of the pipe
			execve(command_path, exec->cmd, envp);
			exit(0);
		}
		else // This is the parent process
		{
			waitpid(exec->pid, NULL, 0);
		 	close(exec->fd[1]); // Close the write end of the pipe in the parent
			dup2(exec->fd[0], STDIN_FILENO); // Replace stdin with the read end of the pipe
		}
		if (command_path != NULL)
			free(command_path);
		exec = exec->next;
		command_path = find_command_path(exec->cmd[0], envp);
	}
	if (command_path == NULL)
	{
		if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
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