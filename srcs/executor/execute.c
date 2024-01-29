/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:08:05 by codespace         #+#    #+#             */
/*   Updated: 2024/01/29 11:44:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_ast **ast, char **envp)
{
	char	**array;
	char	*command_path;
	pid_t	child_pid;
	int		n_cmd;
	int		status;

	n_cmd = 0;
	while ((*ast) != NULL && (*ast)->next != NULL)
	{
		n_cmd++;
		(*ast) = (*ast)->next;
	}
	(*ast) = (*ast)->parent;
	(*ast) = (*ast)->child;
	array = ft_calloc(n_cmd + 2, sizeof(char *));
	n_cmd = 0;
	while ((*ast) != NULL && (*ast)->next != NULL)
	{
		array[n_cmd] = (*ast)->cmd;
		n_cmd++;
		(*ast) = (*ast)->next;
	}
	array[n_cmd] = (*ast)->cmd;
	command_path = find_command_path(array[0], envp);
	if (command_path == NULL)
	{
		if (match_cmd(array[0], array, envp) == false)
			printf("Command not found: %s\n", array[0]);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
			perror("fork");
		else if (child_pid == 0)
		{
			execve(command_path, array, envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
		free(command_path);
		free (array);
		// ft_free_path_env(cmd);
	}
}

void	execute(t_ast **ast, char **envp)
{
	(*ast) = (*ast)->child;
	if ((*ast)->type == PIPE && (*ast)->next == NULL)
	{
		(*ast) = (*ast)->child;
		execute_cmd(ast, envp);
	}
}
