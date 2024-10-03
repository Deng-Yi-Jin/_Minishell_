/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:23:57 by kytan             #+#    #+#             */
/*   Updated: 2024/10/03 21:13:07 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*execute_parent_process(t_execute *execute)
{
	t_count	count;
	char	*result;
	size_t	bytes_read;

	count = (t_count){0, 0, 0, 0};
	close(execute->fd[1]);
	result = ft_calloc(BUFFER_SIZE, sizeof(char));
	bytes_read = read(execute->fd[0], result, BUFFER_SIZE - 1);
	result[bytes_read] = '\0';
	while (count.i < bytes_read)
	{
		if (result[count.i] == '\n')
			result[count.i] = '\t';
		count.i++;
	}
	close(execute->fd[0]);
	waitpid(execute->pid, NULL, 0);
}

char	*handle_fork(t_execute *execute, char *command_path,
		char **cmd, char **envp)
{
	char		*result;

	execute->pid = fork();
	if (execute->pid == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (execute->pid == 0)
	{
		close(execute->fd[0]);
		dup2(execute->fd[1], 1);
		execve(command_path, cmd, envp);
		exit(0);
	}
	else
		result = execute_parent_process(execute);
	free(command_path);
	return (result);
}
