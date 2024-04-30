/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/04/30 15:30:00 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_last_cmd(t_exec *exec, char **envp, char *command_path)
{
	if (create_fork() == 0)
	{
		command_path = find_command_path(exec->cmd[0], envp);
		if (command_path == NULL)
		{
			if (!match_cmd(exec->cmd[0], exec->cmd, envp))
			{
				printf("minishell: %s: command not found\n", exec->cmd[0]);
				exit(127);
			}
		}
		else
		{
			if (exec->prev != NULL && exec->prev->fd[0] != 0)
			{
				close(exec->prev->fd[1]);
				dup2(exec->prev->fd[0], STDIN_FILENO);
				close(exec->prev->fd[0]);
			}
			execve(command_path, exec->cmd, envp);
			perror("execve");
			exit(126);
		}
	}
	else
	{
		if (exec->prev != NULL && exec->prev->fd[0] != 0)
		{
			close(exec->prev->fd[0]);
			close(exec->prev->fd[1]);
		}
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
	if (create_fork() == 0)
	{
		command_path = find_command_path(exec->cmd[0], envp);
		if (command_path == NULL)
		{
			if (!match_cmd(exec->cmd[0], exec->cmd, envp))
			{
				printf("minishell: %s: command not found\n", exec->cmd[0]);
				exit(127);
			}
		}
		else
		{
			manage_pipe_child(exec);
			execve(command_path, exec->cmd, envp);
			perror("execve");
			exit(126);
		}
	}
	else
	{
		manage_pipe_parent(exec);
	}
}

void	start_command_exec(char *command_path, char **envp, t_exec *exec, int saved_stdin)
{
	t_exec	*current_node;

	current_node = exec;
	while (current_node)
	{
		if (!last_cmd(current_node))
		{
			if (pipe(current_node->fd) == -1)
				exit(-1);
			execution(current_node, envp, command_path);
		}
		else
			execute_last_cmd(current_node, envp, command_path);
		current_node = current_node->next;
	}
	while (wait(NULL) > 0);
}

void	execute(t_exec *exec, char **envp)
{
	char	*command_path;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	start_command_exec(command_path, envp, exec, saved_stdin);
}
