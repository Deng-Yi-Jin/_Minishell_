/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:59:30 by codespace         #+#    #+#             */
/*   Updated: 2024/09/24 09:49:29 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_pid(t_exec *exec, char **envp, char *command_path)
{
	close(exec->fd[0]);
	dup2(exec->fd[1], STDOUT_FILENO);
	printf("#2 Exiting process %ld execve()\n", getpid);
	execve(command_path, exec->cmd, envp);
	exit(0);
}

void	exec_parent_pid(t_exec *exec, char **envp, char *command_path)
{
	waitpid(exec->pid, NULL, 0);
	close(exec->fd[1]);
	dup2(exec->fd[0], STDIN_FILENO);
}

void	handle_cmd_path(t_exec *exec, char **envp, char *command_path)
{
	if (command_path == NULL)
		printf("Command not found: %s\n", exec->cmd[0]);
	else
	{
		exec->pid = fork();
		if (exec->pid == 0)
		{
			printf("#3 Exiting process %ld execve()\n", getpid);
			if (execve(command_path, exec->cmd, envp))
				perror("execve");
		}
		else
			waitpid(exec->pid, NULL, 0);
	}
}

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
			exec_child_pid(exec, envp, command_path);
		else
			exec_parent_pid(exec, envp, command_path);
		if (command_path != NULL)
			free(command_path);
		exec = exec->next;
		command_path = find_command_path(exec->cmd[0], envp);
	}
	handle_cmd_path(exec, envp, command_path);
	if (command_path != NULL)
		free(command_path);
	exec = exec->next;
}
