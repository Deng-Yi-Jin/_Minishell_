/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/03/18 13:05:25 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_last_cmd(t_exec *exec, char **envp, char *command_path)
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
}

int	total_command(t_exec *exec, int count)
{
	t_exec	*temp;

	temp = exec;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->cmd[0], "") == 0)
			break;
		count++;
		temp = temp->next;
	}
	return (count);
}

void	execution(t_exec *exec, char **envp, char *command_path)
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
}

void	start_command_exec(char *command_path, char **envp, t_exec *exec, int saved_stdin)
{
	while (exec != NULL)
	{
		command_path = find_command_path(exec->cmd[0], envp);
		if (command_path == NULL)
		{
			if (match_cmd(exec->cmd[0], exec->cmd, envp) == false)
		   		 printf("Command not found: %s\n", exec->cmd[0]);
		}
		else
		{
			while (exec->next)
			{
				execution(exec, envp, command_path);
				free(command_path);
				exec = exec->next;
				command_path = find_command_path(exec->cmd[0], envp);
			}
			execute_last_cmd(exec, envp, command_path);
			free(command_path);
   	 	}
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
		exec = exec->next;
	}
}

void	execute(t_exec *exec, char **envp)
{
	char	*command_path;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	start_command_exec(command_path, envp, exec, saved_stdin);
}
