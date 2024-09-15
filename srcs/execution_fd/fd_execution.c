/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geibo <geibo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:10:22 by geibo             #+#    #+#             */
/*   Updated: 2024/09/15 17:56:06 by geibo            ###   ########.fr       */
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
