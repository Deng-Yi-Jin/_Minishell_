/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kytan <kytan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:10:22 by geibo             #+#    #+#             */
/*   Updated: 2024/09/16 11:30:34 by kytan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_lastcmdredir(t_exec *exec, int infile_fd, int outfile_fd)
{
	if (infile_fd != 0)
	{
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
	}
	if (outfile_fd != 0)
	{
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
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

void	child_infd_setup(int infile_fd)
{
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(infile_fd);
}

void	child_outfd_setup(int outfile_fd)
{
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(outfile_fd);
}
