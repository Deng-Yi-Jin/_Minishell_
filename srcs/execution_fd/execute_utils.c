/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:25 by geibo             #+#    #+#             */
/*   Updated: 2024/09/15 18:09:53 by geibo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(char **envp, t_exec *exec, char *command_path, int *i)
{
	if (check_command(exec->cmd_list[*i], exec->cmd_list, envp) && exec->prev == NULL)
		check_match_cmd(exec, envp, i);
	else if (!check_command(exec->cmd_list[*i], exec->cmd_list, envp))
	{
		command_path = find_command_path(exec->cmd_list[*i], envp);
		if (!command_path)
		{
			printf("minishell: %s: command not found\n", exec->cmd_list[*i]);
			exit(127);
		}
		execve(command_path, exec->cmd_list, envp);
		perror("execve");
		exit(126);
	}
}

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

bool	last_cmd(t_exec *exec)
{
	return (exec->next == NULL);
}

void	manage_pipe_child(t_exec *exec, int infile_fd, int outfile_fd)
{
if (exec->prev != NULL)
{
    close(exec->prev->fd[1]);
    if (dup2(exec->prev->fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(exec->prev->fd[0]);
}

if (infile_fd != 0)
{
    if (dup2(infile_fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(infile_fd);
}

close(exec->fd[0]);

if (outfile_fd != 0)
{
    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(outfile_fd);
}
else
{
    if (dup2(exec->fd[1], STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
}

close(exec->fd[1]);
}

void	manage_pipe_parent(t_exec *exec)
{
	if (exec->prev != NULL && exec->prev->fd[0] != 0)
	{
		close(exec->prev->fd[0]);
		close(exec->prev->fd[1]);
	}
	if (exec->prev != NULL)
	{
		exec->prev->fd[0] = exec->fd[0];
		exec->prev->fd[1] = exec->fd[1];
	}
}
