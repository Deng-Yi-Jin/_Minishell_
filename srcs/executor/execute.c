/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/02/06 04:02:57 by codespace        ###   ########.fr       */
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

void execute_pipeline(t_exec *exec, int n, char **envp)
{
    int i = 0;
    int in_fd = 0; // The input file descriptor. Initially set to stdin.
    int fd[2]; // The file descriptors for the pipe.

    while (i < n)
    {
        pipe(fd); // Create a pipe

        if (fork() == 0)
        {
            if (in_fd != 0)
            {
                dup2(in_fd, 0); // Replace stdin with the input pipe
                close(in_fd); // Close the original file descriptor
            }
            if (fd[1] != 1)
            {
                dup2(fd[1], 1); // Replace stdout with the output pipe
                close(fd[1]); // Close the original file descriptor
            }

            // Execute the command
            char *command_path = find_command_path(exec->cmd[0], envp);
            if (command_path == NULL)
            {
                if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
                    printf("Command not found: %s\n", exec->cmd[0]);
                exit(EXIT_FAILURE);
            }
            else
            {
                execve(command_path, exec->cmd, envp);
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }

        // Close the input side of the pipe, we're done with it
        close(fd[1]);

        // The output side of this pipe will be the input for the next command
        in_fd = fd[0];

        i++;
    }

    // Wait for all child processes to finish
    while (n-- > 0)
        wait(NULL);
}

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

void	execution(t_exec *exec, char **envp)
{
	char	*command_path;

	if (command_path == NULL)
	{
		if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
			printf("Command not found: %s\n", exec->cmd[0]);
	}
	else
	{
		if (execve(command_path, exec->cmd, envp) == -1)
			perror("execve");
	}
}

void	execute(t_exec *exec, char **envp)
{
	char	*command_path;
	pid_t	child_pid;
	int		fd[2];
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
				if (pipe(fd) == -1)
			   	 	perror("pipe");
				exec->pid = fork();
				if (exec->pid == -1)
					perror("fork");
				if (exec->pid == 0) // This is the child process
				{
			   		close(fd[0]); // Close the read end of the pipe in the child
			   		dup2(fd[1], STDOUT_FILENO); // Replace stdout with the write end of the pipe
		   			execve(command_path, exec->cmd, envp);
		   			exit(0);
		   		}
		   		else // This is the parent process
				{
					waitpid(exec->pid, NULL, 0);
		  			close(fd[1]); // Close the write end of the pipe in the parent
			 		dup2(fd[0], STDIN_FILENO); // Replace stdin with the read end of the pipe
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
				{
					waitpid(exec->pid, NULL, 0);
				}
			}
			if (command_path != NULL)
				free(command_path);
			exec = exec->next;
   	 	}
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}
