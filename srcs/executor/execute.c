/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/02/07 10:49:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	after_pipe(t_exec *exec, char **envp, char *command_path)
{
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
}

void	execution(t_exec *exec, char **envp, int *fd, char *command_path)
{
	while (exec->next != NULL)
	{
		if (pipe(fd) == -1)
			perror("pipe");
		exec->pid = fork();
		if (exec->pid == -1)
			perror("fork");
		if (exec->pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execve(command_path, exec->cmd, envp);
			exit(0);
		}
		else
		{
			waitpid(exec->pid, NULL, 0);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
		}
		if (command_path != NULL)
			free(command_path);
		exec = exec->next;
		command_path = find_command_path(exec->cmd[0], envp);
	}
}

// void	execute_single_cmd(t_exec *exec, char **envp)
// {
// 	char	*command_path;
// 	pid_t	child_pid;
// 	int		status;

// 	command_path = find_command_path(exec->cmd[0], envp);
// 	if (command_path == NULL)
// 	{
// 		if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
// 			printf("Command not found: %s\n", exec->cmd[0]);
// 	}
// 	else
// 	{
// 		child_pid = fork();
// 		if (child_pid == -1)
// 			perror("fork");
// 		else if (child_pid == 0)
// 		{
// 			execve(command_path, exec->cmd, envp);
// 			perror("execve");
// 		}
// 		else
// 			waitpid(child_pid, &status, 0);
// 		free(command_path);
// 	}
// }

// void	execute(t_exec *exec, char **envp)
// {
// 	char	*command_path;
// 	pid_t	child_pid;
// 	int		fd[2];
// 	int		saved_stdin;

// 	saved_stdin = dup(STDIN_FILENO);
// 	while (exec != NULL)
// 	{
// 		command_path = find_command_path(exec->cmd[0], envp);
// 		if (command_path == NULL)
// 		{
// 			if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
// 				printf("Command not found: %s\n", exec->cmd[0]);
// 			exec = exec->next;
// 		}
// 		else
// 		{
// 			execution(exec, envp, fd, command_path);
// 			after_pipe(exec, envp, command_path);
// 			exec = exec->next;
// 		}
// 		dup2(saved_stdin, STDIN_FILENO);
// 		close(saved_stdin);
// 	}
// }

void	execute(t_exec *exec, char **envp)
{
	char	*command_path;
	pid_t	child_pid;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	while (exec != NULL)
	{
		command_path = find_command_path(exec->cmd[0], envp);
		if (command_path == NULL)
		{
			if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
		   		 printf("Command not found: %s\n", exec->cmd[0]);
	   	 	exec = exec->next;
		}
		else
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
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}
