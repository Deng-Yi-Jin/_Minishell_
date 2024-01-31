/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/01/31 00:04:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	execute_cmd(t_ast **ast, char **envp)
// {
// 	char	**array;
// 	char	*command_path;
// 	pid_t	child_pid;
// 	int		n_cmd;
// 	int		status;

// 	n_cmd = 0;
// 	while ((*ast) != NULL && (*ast)->next != NULL)
// 	{
// 		n_cmd++;
// 		(*ast) = (*ast)->next;
// 	}
// 	(*ast) = (*ast)->parent;
// 	(*ast) = (*ast)->child;
// 	array = ft_calloc(n_cmd + 2, sizeof(char *));
// 	n_cmd = 0;
// 	while ((*ast) != NULL && (*ast)->next != NULL)
// 	{
// 		array[n_cmd] = (*ast)->cmd;
// 		n_cmd++;
// 		(*ast) = (*ast)->next;
// 	}
// 	array[n_cmd] = (*ast)->cmd;
// 	command_path = find_command_path(array[0], envp);
// 	if (command_path == NULL)
// 	{
// 		if (match_cmd(array[0], array, envp) == false)
// 			printf("Command not found: %s\n", array[0]);
// 	}
// 	else
// 	{
// 		child_pid = fork();
// 		if (child_pid == -1)
// 			perror("fork");
// 		else if (child_pid == 0)
// 		{
// 			execve(command_path, array, envp);
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			waitpid(child_pid, &status, 0);
// 		}
// 		free(command_path);
// 		free (array);
// 		// ft_free_path_env(cmd);
// 	}
// }

void	execute_single_cmd(t_exec *exec, char **envp)
{
	char	*command_path;
	pid_t	child_pid;
	int		status;

	command_path = find_command_path(exec->cmd[0], envp);
	if (command_path == NULL)
	{
		if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
			printf("Command not found: %s\n", exec->cmd[0]);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
			perror("fork");
		else if (child_pid == 0)
		{
			execve(command_path, exec->cmd, envp);
			perror("execve");
			// exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
		free(command_path);
		// ft_free_path_env(cmd);
	}
}

// void execute_cmd(char **cmd, char **envp)
// {
// 	char *command_path;
// 	pid_t child_pid;
// 	int status;

// 	command_path = find_command_path(cmd[0], envp);
// 	child_pid = fork();
// 	if (child_pid == -1)
// 	{
// 		perror("fork");
// 		return;
// 	}
// 	if (child_pid == 0) // This is the child process
// 	{
// 		if (execve(command_path, cmd, envp) == -1)
// 			perror("execve");
// 		exit(EXIT_SUCCESS);
// 	}
// 	else // This is the parent process
// 	{
// 		wait(&status); // Wait for the child to finish
// 	}
// }

void	execute(t_exec *exec, char **envp)
{
	char	*command_path;
	pid_t	child_pid;
	int		fd[2];

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
				if (pipe(fd) == -1)
			   	 	perror("pipe");
				exec->pid = fork();
				if (exec->pid == -1)
					perror("fork");
				if (exec->pid == 0) // This is the child process
				{
			   		dup2(fd[1], STDOUT_FILENO); // Replace stdout with the write end of the pipe
			   		close(fd[0]); // Close the read end of the pipe in the child
		   			execve(command_path, exec->cmd, envp);
		   			//  exit(EXIT_FAILURE);
		   		}
		   		else // This is the parent process
				{
					waitpid(exec->pid, NULL, 0);
			 		dup2(fd[0], STDIN_FILENO); // Replace stdin with the read end of the pipe
		  			close(fd[1]); // Close the write end of the pipe in the parent
		  		}
		   		exec = exec->next;
		  		command_path = find_command_path(exec->cmd[0], envp);
	   		}
			printf("check5\n");
	   		execve(command_path, exec->cmd, envp);
			// execute_single_cmd(exec, envp);
   	 	}
	}
}