/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:59:30 by codespace         #+#    #+#             */
/*   Updated: 2024/10/03 19:33:50 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_pid(t_exec *exec, char **envp, char *command_path)
{
	close(exec->fd[0]);
	dup2(exec->fd[1], STDOUT_FILENO);
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

// void	update_g_envp()
// {
// 	char	**envp_array;
// 	int		i;

// 	i = -1;
// 	free_split(envp);
// 	envp_array = ft_calloc(total_g_env_vars() + 1, sizeof(char *));
// 	while (g_main->env_vars[++i]->key != NULL)
// 	{
// 		envp_array[i] = ft_strdup(g_main->env_vars[i]->key); //PATH
// 		envp_array[i] = ft_strfjoin(envp_array[i], "=");
// 		envp_array[i] = ft_strfjoin(envp_array[i], g_main->env_vars[i]->value);
// 	}
// 	envp = envp_array;
// }